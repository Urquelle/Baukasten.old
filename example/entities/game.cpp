#include "game.h"
#include "forms/ogre_form.h"
#include "lua/bindings.h"
#include "world_map.h"

#include <generic_state.h>
#include <graphics_interface.h>
#include <igraphics.h>
#include <lua/action.h>

using namespace Baukasten;

Game::Game( const std::string &id ) :
	GameEntity( id ),
	mGraphics( GraphicsInterface::instance() )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );
	addAction( new ActionLua( *this, "updateState", "scripts/update_state.lua" ) );
	setForm( new Form( "form" ) );
}

Game::~Game()
{
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

void Game::run()
{
	// mainloop
	while ( keepRunning() ) {
		invokeAction( "updateState" );
		invokeAction( "processInput" );

		runActions();
		mGraphics->render();
	}

	std::cout << "... GAME OVER!!! ..." << endl;
}

int Game::init()
{
	initBindings();
	mGraphics->init();

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );
	mWorldMap->setForm( new OgreForm( "form" ) );

	addChild( mWorldMap );

	mGraphics->addForm( mWorldMap->getForm() );
}

