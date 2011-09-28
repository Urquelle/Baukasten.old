#include "game.h"

#include "actions.h"
#include "block_form.h"
#include "form2d.h"

#include <lua/action_lua.h>
#include <core_services.h>
#include <generic_state.h>
#include <iinput.h>
#include <igraphics.h>
#include <logical_space.h>
#include <virtual_space.h>

using namespace Baukasten;

Game::Game( const string &id ) :
	GameEntity( id )
{
	addAction( new ActionLua( *this, "action:rotateLeft", "scripts/rotate_left.lua" ) );
	addAction( new ActionLua( *this, "action:rotateRight", "scripts/rotate_right.lua" ) );
	addAction( new ActionLambda( *this, "action:moveLeft", &moveLeft ) );
	addAction( new ActionLambda( *this, "action:moveRight", &moveRight ) );

	addState( new StateBool( "state:keepRunning", true ) );

	setForm( new Form( "form:main" ) );
}

Game::~Game()
{
}

void Game::start()
{
	init();
	run();
}

void Game::init()
{
	CoreServices* service = CoreServices::instance();

	service->init();
	mInput = service->getInputService();
	mGraphics = service->getVideoService();

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
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0
	}));

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
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0
	}));

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
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 1, 0
	}));

	GameEntity *blockL = new GameEntity( "block:l" );
	blockL->setForm( new BlockForm( "form:l", mGraphics ) );
	blockL->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockL->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0,
		0, 0, 0, 0
	}));

	GameEntity *blockJ = new GameEntity( "block:j" );
	blockJ->setForm( new BlockForm( "form:j", mGraphics ) );
	blockJ->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockJ->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 1, 1, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));

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
		1, 1, 1, 1,
		0, 0, 0, 0
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
		1, 1, 1, 1,
		0, 0, 0, 0
	}));

	GameEntity *blockGroup = new GameEntity( "entity:group" );
	blockGroup->addAction( new ActionLua( *blockGroup, "action:nextBlock", "scripts/next_block.lua" ) );
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
	case Key::KEY_Q:
		getState<StateBool*>( "state:keepRunning" )->setValue( false );
		break;
	case Key::KEY_ARROW_UP:
		invokeAction( "action:rotateRight" );
		break;
	case Key::KEY_ARROW_DOWN:
		invokeAction( "action:rotateLeft" );
		break;
	case Key::KEY_ARROW_RIGHT:
		invokeAction( "action:moveRight" );
		break;
	case Key::KEY_ARROW_LEFT:
		invokeAction( "action:moveLeft" );
		break;
	}
}

