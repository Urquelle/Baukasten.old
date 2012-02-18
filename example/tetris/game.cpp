#include "game.h"

#include "actions.h"
#include "block_form.h"
#include "field_form.h"
#include "form2d.h"
#include "score_form.h"

#include "audio/IAudio"
#include "core/CoreServices"
#include "graphics/IGraphics"
#include "input/IInput"
#include "model/ActionLua"
#include "model/GenericState"
#include "model/LogicalSpace"
#include "model/VirtualSpace"

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

	mInput = service->inputService();
	mGraphics = service->videoService();
	mGraphics->createWindow( { 1024, 768 }, L"Tetris" );
	mAudio = service->audioService();

	mAudio->loadFile( "media/tetris_theme.wav", "audio:main" );
	mAudio->play( "audio:main", 0, 0, true );

	mInput->onKeyDown()->connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init main display
	GameEntity *display = new GameEntity( "entity:display ");
	display->setForm(
		new Form2d( "form:display", "media/display.png", mGraphics )
	);

	display->form()->setPosition( { 0, 0, 0 } );
	display->form()->setSize( { 1024, 768 } );

	addChild( display );
	form()->addToVSpace( display->form() );
	form()->addToLSpace( display );

	// init playfield
	GameEntity *field = new GameEntity( "entity:field" );
	field->addAction( new ActionLambda( *field, "action:recalculate", &recalc, &recalcDone ) );
	field->addAction( new ActionLambda( *field, "action:clearCompleteRows", &clearCompleteRows ) );
	field->addState( new StateInt( "state:column", 0 ) );
	field->addState( new StateInt( "state:row", 0 ) );
	field->addState( new StateInt( "state:rows", 18 ) );
	field->setForm( new FieldForm( "form:field", mGraphics ) );
	field->form()->addState( new StateIntVector( "block:current" ) );
	field->form()->addState( new StateInt( "state:step", 0 ) );
	field->form()->addState( new StateInt( "block:column", 5 ) );
	field->form()->addState( new StateInt( "block:row", 0 ) );
	field->form()->setPosition( { 240, 20, 0 } );
	field->form()->setSize( { 480, 720 } );

	// 12x18
	field->form()->addState( new StateIntVector( "state:field", {
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
	form()->addToVSpace( field->form() );
	form()->addToLSpace( field );
	field->invokeAction( "action:recalculate" );

	// init blocks
	GameEntity *blockO = new GameEntity( "block:o" );
	blockO->setForm( new BlockForm( "form:o", mGraphics ) );
	blockO->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockO->form()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->form()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->form()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->form()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->form()->addState( new StateIntVector( "state:matrix",
		blockO->form()->state<StateIntVector*>( "state:matrix1" )->values()
	));

	GameEntity *blockZ = new GameEntity( "block:z" );
	blockZ->setForm( new BlockForm( "form:z", mGraphics ) );
	blockZ->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockZ->form()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->form()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockZ->form()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->form()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockZ->form()->addState( new StateIntVector( "state:matrix",
		blockZ->form()->state<StateIntVector*>( "state:matrix1" )->values()
	));

	GameEntity *blockS = new GameEntity( "block:s" );
	blockS->setForm( new BlockForm( "form:s", mGraphics ) );
	blockS->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockS->form()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->form()->addState( new StateIntVector( "state:matrix2", {
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockS->form()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->form()->addState( new StateIntVector( "state:matrix4", {
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockS->form()->addState( new StateIntVector( "state:matrix",
		blockS->form()->state<StateIntVector*>( "state:matrix1" )->values()
	));

	GameEntity *blockT = new GameEntity( "block:t" );
	blockT->setForm( new BlockForm( "form:t", mGraphics ) );
	blockT->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockT->form()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockT->form()->addState( new StateIntVector( "state:matrix2", {
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockT->form()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockT->form()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockT->form()->addState( new StateIntVector( "state:matrix",
		blockT->form()->state<StateIntVector*>( "state:matrix1" )->values()
	));

	GameEntity *blockL = new GameEntity( "block:l" );
	blockL->setForm( new BlockForm( "form:l", mGraphics ) );
	blockL->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockL->form()->addState( new StateIntVector( "state:matrix1", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockL->form()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockL->form()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockL->form()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0,
		0, 0, 0, 0
	}));
	blockL->form()->addState( new StateIntVector( "state:matrix",
		blockL->form()->state<StateIntVector*>( "state:matrix1" )->values()
	));

	GameEntity *blockJ = new GameEntity( "block:j" );
	blockJ->setForm( new BlockForm( "form:j", mGraphics ) );
	blockJ->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockJ->form()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->form()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->form()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockJ->form()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->form()->addState( new StateIntVector( "state:matrix",
		blockJ->form()->state<StateIntVector*>( "state:matrix1" )->values()
	));

	GameEntity *blockI = new GameEntity( "block:i" );
	blockI->setForm( new BlockForm( "form:i", mGraphics ) );
	blockI->form()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockI->form()->addState( new StateIntVector( "state:matrix1", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockI->form()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1
	}));
	blockI->form()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockI->form()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1
	}));
	blockI->form()->addState( new StateIntVector( "state:matrix",
		blockI->form()->state<StateIntVector*>( "state:matrix1" )->values()
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
	form()->addToLSpace( blockGroup );

	// create and add the score window object
	GameEntity *score = new GameEntity( "entity:score" );
	score->addState( new StateInt( "state:score", 0 ) );
	score->addState( new StateInt( "state:linesCleared", 0 ) );
	score->addAction( new ActionLambda( *score, "action:collectPoints", &collectPoints ) );
	score->setForm( new ScoreForm( "form:score", mGraphics ) );
	score->form()->addState( new StateInt( "state:score", 0 ) );
	score->form()->setPosition( { 800, 300, 0 } );

	addChild( score );
	form()->addToLSpace( score );
	form()->addToVSpace( score->form() );
}

void Game::run()
{
	while ( state<StateBool*>( "state:keepRunning" )->value() ) {
		runActions();
		mInput->process();
		mGraphics->render( form() );
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
		state<StateBool*>( "state:keepRunning" )->setValue( false );
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

