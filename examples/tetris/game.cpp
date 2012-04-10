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
#include "model/ModelInterface"
#include "model/VirtualSpace"
#include "services/Services"

using namespace Baukasten;

Game::Game( const string &id, int argc, char **argv ) :
	m_game( 0 ),
	m_argc( argc ),
	m_argv( argv )
{
	m_game = ModelInterface::instance().createEntity( id );

	m_game->addAction( new ActionLua( *m_game, "action:rotate", "scripts/rotate.lua" ) );
	m_game->addAction( new ActionLambda( *m_game, "action:moveLeft", moveLeft ) );
	m_game->addAction( new ActionLambda( *m_game, "action:moveRight", moveRight ) );

	m_game->addAction( new ActionLambda( *m_game, "action:pause",
		([]( Action *action, GameEntity *entity ) {
			entity->state<StateBool*>( "state:pause" )->setValue(
				!entity->state<StateBool*>( "state:pause" )->value()
			);
		})
	) );

	m_game->addAction( new ActionLambda( *m_game, "action:gameOver",
		([]( Action *action, GameEntity *field ) {
		 	field->dropAction( "action:recalculate" );
		})
	) );

	m_game->addState( new StateBool( "state:keepRunning", true ) );
	m_game->addState( new StateBool( "state:pause", false ) );

	m_game->setForm( new Form( "form:main" ) );
}

Game::~Game()
{
	Services::instance().shutdown();
	ModelInterface::instance().shutdown();
}

void Game::start()
{
	init();
	run();
}

void Game::init()
{
	Services &service = Services::instance();
	ModelInterface &model = ModelInterface::instance();

	service.init( m_argc, m_argv );

	IInput &m_input = service.inputService();
	IGraphics &m_graphics = service.videoService();
	IAudio &m_audio = service.audioService();

	m_graphics.createWindow( { 1024, 768 }, "Tetris" );

	m_audio.loadFile( "media/tetris_theme.wav", "audio:main" );
	m_audio.setVolume( "audio:main", 0.3 );
	m_audio.setLoop( "audio:main", true );
	//m_audio->play( "audio:main" );

	m_input.onKeyDown()->connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init main display
	GameEntity *display = model.createEntity( "entity:display ", m_game );
	display->setForm(
		new Form2d( "form:display", "media/display.png" )
	);

	display->form()->setPosition( { 0, 0, 0 } );
	display->form()->setSize( { 1024, 768 } );

	m_game->addChild( display );
	m_game->form()->addToVSpace( display->form() );
	m_game->form()->addToLSpace( display );

	// init playfield
	GameEntity *field = model.createEntity( "entity:field", m_game );
	field->addAction( new ActionLambda( *field, "action:recalculate", recalc, false ) );
	field->addAction( new ActionLambda( *field, "action:clearCompleteRows", clearCompleteRows ) );
	field->addState( new StateInt( "state:column", 0 ) );
	field->addState( new StateInt( "state:row", 0 ) );
	field->addState( new StateInt( "state:rows", 18 ) );
	field->setForm( new FieldForm( "form:field" ) );
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

	m_game->addChild( field );
	m_game->form()->addToVSpace( field->form() );
	m_game->form()->addToLSpace( field );
	field->invokeAction( "action:recalculate" );

	GameEntity *blockGroup = model.createEntity( "entity:group", m_game );

	// init blocks
	GameEntity *blockO = model.createEntity( "block:o", blockGroup );
	blockO->setForm( new BlockForm( "form:o" ) );
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

	GameEntity *blockZ = model.createEntity( "block:z", blockGroup );
	blockZ->setForm( new BlockForm( "form:z" ) );
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

	GameEntity *blockS = model.createEntity( "block:s", blockGroup );
	blockS->setForm( new BlockForm( "form:s" ) );
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

	GameEntity *blockT = model.createEntity( "block:t", blockGroup );
	blockT->setForm( new BlockForm( "form:t" ) );
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

	GameEntity *blockL = model.createEntity( "block:l", blockGroup );
	blockL->setForm( new BlockForm( "form:l" ) );
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

	GameEntity *blockJ = model.createEntity( "block:j", blockGroup );
	blockJ->setForm( new BlockForm( "form:j" ) );
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

	GameEntity *blockI = model.createEntity( "block:i", blockGroup );
	blockI->setForm( new BlockForm( "form:i" ) );
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

	blockGroup->addAction( new ActionLambda( *blockGroup, "action:nextBlock", nextBlock ) );
	blockGroup->addChild( blockO );
	blockGroup->addChild( blockZ );
	blockGroup->addChild( blockS );
	blockGroup->addChild( blockT );
	blockGroup->addChild( blockL );
	blockGroup->addChild( blockJ );
	blockGroup->addChild( blockI );

	m_game->addChild( blockGroup );
	blockGroup->invokeAction( "action:nextBlock" );
	m_game->form()->addToLSpace( blockGroup );

	// create and add the score window object
	GameEntity *score = model.createEntity( "entity:score", m_game );
	score->addState( new StateInt( "state:score", 0 ) );
	score->addState( new StateInt( "state:linesCleared", 0 ) );
	score->addAction( new ActionLambda( *score, "action:collectPoints", collectPoints ) );
	score->setForm( new ScoreForm( "form:score" ) );
	score->form()->addState( new StateInt( "state:score", 0 ) );
	score->form()->setPosition( { 800, 300, 0 } );

	m_game->addChild( score );
	m_game->form()->addToLSpace( score );
	m_game->form()->addToVSpace( score->form() );
}

void Game::run()
{
	while ( m_game->state<StateBool*>( "state:keepRunning" )->value() ) {
		m_game->runActions();
		Services::instance().inputService().process();
		Services::instance().videoService().render( m_game->form() );
	}
}

void Game::onKeyDown( Key key, Modifier mod )
{
	switch ( key ) {
	case Key::KEY_P:
	case Key::KEY_SPACE:
		m_game->invokeAction( "action:pause" );
		break;
	case Key::KEY_Q:
		m_game->state<StateBool*>( "state:keepRunning" )->setValue( false );
		break;
	case Key::KEY_ARROW_UP:
		m_game->invokeAction( "action:rotate" );
		break;
	case Key::KEY_ARROW_DOWN:
		break;
	case Key::KEY_ARROW_RIGHT:
		m_game->invokeAction( "action:moveRight" );
		break;
	case Key::KEY_ARROW_LEFT:
		m_game->invokeAction( "action:moveLeft" );
		break;
	}
}

