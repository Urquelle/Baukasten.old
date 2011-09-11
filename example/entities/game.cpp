#include "game.h"

#include "basic_type.h"
#include "entities/unit.h"
#include "../lua/bindings.h"
#include "world_map.h"

#include <core_services.h>
#include <debug.h>
#include <form.h>
#include <generic_state.h>
#include <lua/action_lua.h>
#include <irrlicht/irrlicht_graphics.h>
#include <irrlicht/irrlicht_input.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;

enum Mode { MODE_WORLDMAP, MODE_MENU, MODE_BATTLE };

Game::Game( const std::string &id ) :
	GameEntity( id ),
	mWorldMap( 0 ), mGraphics( 0 ), mInput( 0 ),
	mMoveRight( false ), mMoveLeft( false ),
	mMoveUp( false ), mMoveDown( false )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );
	addState( "currentMode", new StateInt( "currentMode", MODE_WORLDMAP ) );

	addAction( new ActionLua( *this, "updateState", "scripts/update_state.lua" ) );

	setForm( new Form( "form" ) );
}

Game::~Game()
{
	mInput->shutDown();
	mGraphics->shutDown();
}

void Game::start()
{
	init();
	run();
}

bool Game::keepRunning()
{
	return getState<StateInt*>( "keepRunning" )->getValue();
}

void Game::onKeyDown( Key key, Modifier mod )
{
	switch ( key ) {
	case KEY_Q:
		getState<StateInt*>( "keepRunning" )->setValue( 0 );
		break;
	case KEY_ARROW_LEFT:
		if ( mod & KEYMOD_PRESSED && !mMoveLeft ) {
			mWorldMap->invokeAction( "moveLeftOnMap" );
			mMoveLeft = true;
		} else if ( mod & KEYMOD_RELEASED ) {
			mMoveLeft = false;
		}
		break;
	case KEY_ARROW_UP:
		if ( mod & KEYMOD_PRESSED && !mMoveUp ) {
			BK_DEBUG( "move up" );
			mMoveUp = true;
		} else if ( mod & KEYMOD_RELEASED ) {
			mMoveUp = false;
		}
		break;
	case KEY_ARROW_RIGHT:
		if ( mod & KEYMOD_PRESSED && !mMoveRight ) {
			mWorldMap->invokeAction( "moveRightOnMap" );
			mMoveRight = true;
		} else if ( mod & KEYMOD_RELEASED ) {
			mMoveRight = false;
		}
		break;
	case KEY_ARROW_DOWN:
		if ( mod & KEYMOD_PRESSED && !mMoveDown ) {
			BK_DEBUG( "move down" );
			mMoveDown = true;
		} else if ( mod & KEYMOD_RELEASED ) {
			mMoveDown = false;
		}
		break;
	}
}

void Game::run()
{
	// mainloop
	while ( keepRunning() ) {
		invokeAction( "updateState" );

		runActions();
		mInput->process();
		mGraphics->render( getForm() );
	}

	std::cout << "... GAME OVER!!! ..." << endl;
}

int Game::init()
{
	initBindings();

	CoreServices *services = CoreServices::instance();

	services->init();

	mInput = dynamic_cast<IrrlichtInput*>( services->getInputService() );
	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );
	mGraphics = dynamic_cast<IrrlichtGraphics*>( services->getVideoService() );
	mGraphics->getDevice()->setWindowCaption( L"Eisenfaust" );

	// init worldmap
	mWorldMap = new WorldMap( "entity:worldmap" );
	getForm()->addToVSpace( mWorldMap->getForm() );

	// init hero's group and some units
	BasicType *type = new BasicType( "basic" );
	GameEntity *group = new GameEntity( "entity:heroGroup" );

	Unit *sanchez = new Unit( "unit:sanchez" );
	Unit *gomez = new Unit( "unit:gomez" );
	Unit *ramirez = new Unit( "unit:ramirez" );

	sanchez->setType( type );
	gomez->setType( type );
	ramirez->setType( type );

	sanchez->setName( sanchez->getId() );
	gomez->setName( gomez->getId() );
	ramirez->setName( ramirez->getId() );

	group->addChild( sanchez );
	group->addChild( gomez );
	group->addChild( ramirez );

	addChild( mWorldMap );
	addChild( group );
}

