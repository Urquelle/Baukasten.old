#include "game.h"
#include "lua/bindings.h"
#include "world_map.h"
#include "forms/worldmap_form.h"

#include <core_services.h>
#include <generic_state.h>
#include <sdl/sdl_interface.h>
#include <lua/action.h>
#include <ogre/ogre_form.h>
#include <ogre/ogre_interface.h>

using namespace Baukasten;

enum Mode { MODE_WORLDMAP, MODE_MENU, MODE_BATTLE };

Game::Game( const std::string &id ) :
	GameEntity( id )
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

	CoreServices *services = new CoreServices();

	services->init( ALL );

	mInput = dynamic_cast<SDLInterface*>( services->getInputService() );
	mGraphics = dynamic_cast<OgreInterface*>( services->getVideoService() );

	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );

	WorldMapForm *form = new WorldMapForm(
		"form:worldmap",
		mGraphics
	);

	mWorldMap->setForm( form );

	addChild( mWorldMap );
}

