#include "game.h"

#include "actions.h"
#include "block_form.h"
#include "field_form.h"
#include "form2d.h"
#include "score_form.h"

#include "audio/IAudio"
#include "core/ActionLua"
#include "core/GenericState"
#include "core/LogicalSpace"
#include "core/VirtualSpace"
#include "core/CoreServices"
#include "graphics/IGraphics"
#include "input/IInput"

using namespace Baukasten;

Game::Game( const string &id, int argc, char **argv ) :
	GameEntity( id ),
	mAudio( 0 ),
	mGraphics( 0 ),
	mInput( 0 ),
	mArgc( argc ),
	mArgv( argv )
{
	addAction( new ActionLua( *this, "action:rotate", "scripts/rotate.lua" ) );
	addAction( new ActionLambda( *this, "action:moveLeft", &moveLeft ) );
	addAction( new ActionLambda( *this, "action:moveRight", &moveRight ) );
	addAction( new ActionLambda( *this, "action:pause", &pauseGame ) );
	addAction( new ActionLambda( *this, "action:gameOver", &gameOver ) );

	addState( new StateBool( "state:keepRunning", true ) );
	addState( new StateBool( "state:pause", false ) );

	setForm( new Form( "form:main" ) );
}

Game::~Game()
{
	CoreServices* service = CoreServices::instance();
	service->shutdown();
}

void Game::start()
{
	init();
	run();
}

void Game::init()
{
	CoreServices* service = CoreServices::instance();

	service->init( mArgc, mArgv );

	mInput = service->getInputService();
	mGraphics = service->getVideoService();
	mGraphics->createWindow( { 1024, 768 }, L"Tetris" );
	mAudio = service->getAudioService();

	mAudio->loadFile( "media/tetris_theme.wav", "audio:main" );
	mAudio->play( "audio:main", 0, 0, true );

	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init main display
	GameEntity *display = new GameEntity( "entity:display ");
	display->setForm(
		new Form2d( "form:display", "media/display.png", mGraphics )
	);

	display->getForm()->setPosition( { 0, 0, 0 } );
	display->getForm()->setSize( { 1024, 768 } );

	addChild( display );
	getForm()->addToVSpace( display->getForm() );
	getForm()->addToLSpace( display );

	// init playfield
	GameEntity *field = new GameEntity( "entity:field" );
	field->addAction( new ActionLambda( *field, "action:recalculate", &recalc, &recalcDone ) );
	field->addAction( new ActionLambda( *field, "action:clearCompleteRows", &clearCompleteRows ) );
	field->addState( new StateInt( "state:column", 0 ) );
	field->addState( new StateInt( "state:row", 0 ) );
	field->addState( new StateInt( "state:rows", 18 ) );
	field->setForm( new FieldForm( "form:field", mGraphics ) );
	field->getForm()->addState( new StateIntVector( "block:current" ) );
	field->getForm()->addState( new StateInt( "state:step", 0 ) );
	field->getForm()->addState( new StateInt( "block:column", 5 ) );
	field->getForm()->addState( new StateInt( "block:row", 0 ) );
	field->getForm()->setPosition( { 240, 20, 0 } );
	field->getForm()->setSize( { 480, 720 } );

	// 12x18
	field->getForm()->addState( new StateIntVector( "state:field", {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}));

	addChild( field );
	getForm()->addToVSpace( field->getForm() );
	getForm()->addToLSpace( field );
	field->invokeAction( "action:recalculate" );

	// init blocks
	GameEntity *blockO = new GameEntity( "block:o" );
	blockO->setForm( new BlockForm( "form:o", mGraphics ) );
	blockO->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockO->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix",
		blockO->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockZ = new GameEntity( "block:z" );
	blockZ->setForm( new BlockForm( "form:z", mGraphics ) );
	blockZ->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockZ->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix",
		blockZ->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockS = new GameEntity( "block:s" );
	blockS->setForm( new BlockForm( "form:s", mGraphics ) );
	blockS->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockS->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix",
		blockS->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockT = new GameEntity( "block:t" );
	blockT->setForm( new BlockForm( "form:t", mGraphics ) );
	blockT->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockT->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix",
		blockT->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockL = new GameEntity( "block:l" );
	blockL->setForm( new BlockForm( "form:l", mGraphics ) );
	blockL->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockL->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0,
		0, 0, 0, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix",
		blockL->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockJ = new GameEntity( "block:j" );
	blockJ->setForm( new BlockForm( "form:j", mGraphics ) );
	blockJ->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockJ->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix",
		blockJ->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockI = new GameEntity( "block:i" );
	blockI->setForm( new BlockForm( "form:i", mGraphics ) );
	blockI->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockI->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix",
		blockI->getForm()->getState<StateIntVector*>( "state:matrix1" )->getValues()
	));

	GameEntity *blockGroup = new GameEntity( "entity:group" );
	blockGroup->addAction( new ActionLambda( *blockGroup, "action:nextBlock", &nextBlock ) );
	blockGroup->addChild( blockO );
	blockGroup->addChild( blockZ );
	blockGroup->addChild( blockS );
	blockGroup->addChild( blockT );
	blockGroup->addChild( blockL );
	blockGroup->addChild( blockJ );
	blockGroup->addChild( blockI );

	addChild( blockGroup );
	blockGroup->invokeAction( "action:nextBlock" );
	getForm()->addToLSpace( blockGroup );

	// create and add the score window object
	GameEntity *score = new GameEntity( "entity:score" );
	score->addState( new StateInt( "state:score", 0 ) );
	score->addState( new StateInt( "state:linesCleared", 0 ) );
	score->addAction( new ActionLambda( *score, "action:collectPoints", &collectPoints ) );
	score->setForm( new ScoreForm( "form:score", mGraphics ) );
	score->getForm()->addState( new StateInt( "state:score", 0 ) );
	score->getForm()->setPosition( { 800, 300, 0 } );

	addChild( score );
	getForm()->addToLSpace( score );
	getForm()->addToVSpace( score->getForm() );
}

void Game::run()
{
	while ( getState<StateBool*>( "state:keepRunning" )->getValue() ) {
		runActions();
		mInput->process();
		mGraphics->render( getForm() );
	}
}

void Game::onKeyDown( Key key, Modifier mod )
{
	switch ( key ) {
	case Key::KEY_P:
	case Key::KEY_SPACE:
		invokeAction( "action:pause" );
		break;
	case Key::KEY_Q:
		getState<StateBool*>( "state:keepRunning" )->setValue( false );
		break;
	case Key::KEY_ARROW_UP:
		invokeAction( "action:rotate" );
		break;
	case Key::KEY_ARROW_DOWN:
		break;
	case Key::KEY_ARROW_RIGHT:
		invokeAction( "action:moveRight" );
		break;
	case Key::KEY_ARROW_LEFT:
		invokeAction( "action:moveLeft" );
		break;
	}
}

