#include "game.h"

#include "actions.h"
#include "block_form.h"
#include "field_form.h"
#include "form2d.h"
#include "score_form.h"

#include "audio/IAudio"
#include "graphics/IGraphics"
#include "input/IInput"
#include "model/ActionLua"
#include "model/GenericState"
#include "model/LogicalSpace"
#include "model/VirtualSpace"
#include "services/Services"

using namespace Baukasten;

Game::Game( const string &id, int argc, char **argv ) :
	GameEntity( id ),
	m_audio( 0 ),
	m_graphics( 0 ),
	m_input( 0 ),
	m_argc( argc ),
	m_argv( argv )
{
	addAction( new ActionLua( *this, "action:rotate", "scripts/rotate.lua" ) );
	addAction( new ActionLambda( *this, "action:moveLeft", moveLeft ) );
	addAction( new ActionLambda( *this, "action:moveRight", moveRight ) );

	addAction( new ActionLambda( *this, "action:pause",
		([]( Action *action, GameEntity *entity ) {
			entity->state<StateBool*>( "state:pause" )->setValue(
				!entity->state<StateBool*>( "state:pause" )->value()
			);
		})
	) );

	addAction( new ActionLambda( *this, "action:gameOver",
		([]( Action *action, GameEntity *field ) {
		 	field->dropAction( "action:recalculate" );
		})
	) );

	addState( new StateBool( "state:keepRunning", true ) );
	addState( new StateBool( "state:pause", false ) );

	setForm( new Form( "form:main" ) );
}

Game::~Game()
{
	Services* service = Services::instance();
	service->shutdown();
}

void Game::start()
{
	init();
	run();
}

void Game::init()
{
	Services* service = Services::instance();

	service->init( m_argc, m_argv );

	m_input = service->inputService();
	m_graphics = service->videoService();
	m_graphics->createWindow( { 1024, 768 }, L"Tetris" );
	m_audio = service->audioService();

	m_audio->loadFile( "media/tetris_theme.wav", "audio:main" );
	m_audio->setVolume( "audio:main", 0.3 );
	//m_audio->play( "audio:main", 0, 0, true );

	m_input->onKeyDown()->connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init main display
	GameEntity *display = new GameEntity( "entity:display ");
	display->setForm(
		new Form2d( "form:display", "media/display.png", m_graphics )
	);

	display->form()->setPosition( { 0, 0, 0 } );
	display->form()->setSize( { 1024, 768 } );

	addChild( display );
	form()->addToVSpace( display->form() );
	form()->addToLSpace( display );

	// init playfield
	GameEntity *field = new GameEntity( "entity:field" );
	field->addAction( new ActionLambda( *field, "action:recalculate", recalc, false ) );
	field->addAction( new ActionLambda( *field, "action:clearCompleteRows", clearCompleteRows ) );
	field->addState( new StateInt( "state:column", 0 ) );
	field->addState( new StateInt( "state:row", 0 ) );
	field->addState( new StateInt( "state:rows", 18 ) );
	field->setForm( new FieldForm( "form:field", m_graphics ) );
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
	blockO->setForm( new BlockForm( "form:o", m_graphics ) );
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
	blockZ->setForm( new BlockForm( "form:z", m_graphics ) );
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
	blockS->setForm( new BlockForm( "form:s", m_graphics ) );
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
	blockT->setForm( new BlockForm( "form:t", m_graphics ) );
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
	blockL->setForm( new BlockForm( "form:l", m_graphics ) );
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
	blockJ->setForm( new BlockForm( "form:j", m_graphics ) );
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
	blockI->setForm( new BlockForm( "form:i", m_graphics ) );
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
	blockGroup->addAction( new ActionLambda( *blockGroup, "action:nextBlock", nextBlock ) );
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
	score->addAction( new ActionLambda( *score, "action:collectPoints", collectPoints ) );
	score->setForm( new ScoreForm( "form:score", m_graphics ) );
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
		m_input->process();
		m_graphics->render( form() );
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

