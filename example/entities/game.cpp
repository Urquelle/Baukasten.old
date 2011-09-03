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
	mGraphics( GraphicsInterface::instance() ),
	mInput( new InputInterface() )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );
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
	if ( key == Baukasten::KEY_Q ) {
		getState<StateInt*>( "keepRunning" )->setValue( 0 );
	}
}

void Game::run()
{
	// mainloop
	while ( keepRunning() ) {
		invokeAction( "updateState" );

		runActions();
		mGraphics->render();
		mInput->process();
	}

	std::cout << "... GAME OVER!!! ..." << endl;
}

int Game::init()
{
	initBindings();

	// input has to be initialised before graphics, since we use sdl
	// and the window is created there. ogre simply connects to the
	// existing window.
	mInput->init();
	mGraphics->init();

	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );
	mWorldMap->setForm( new OgreForm( "form" ) );

	addChild( mWorldMap );

	mGraphics->addForm( mWorldMap->getForm() );
}

