#include "example_game.h"
#include "forms/ogre_form.h"
#include "lua/bindings.h"
#include "world_map.h"

#include <generic_state.h>
#include <graphics_interface.h>
#include <igraphics.h>
#include <lua/action.h>

using namespace Baukasten;

ExampleGame::ExampleGame( const std::string &id ) :
	GameEntity( id ),
	mGraphics( GraphicsInterface::instance() )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );
	addAction( new ActionLua( *this, "updateState", "scripts/update_state.lua" ) );
	setForm( new Form( "form" ) );
}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::start()
{
	init();
    run();
}

bool ExampleGame::keepRunning() const
{
	return getState<StateInt*>( "keepRunning" )->getValue();
}

void ExampleGame::run()
{
	// mainloop
	while ( keepRunning() ) {
		invokeAction( "updateState" );
		invokeAction( "processInput" );

		runActions();
		mGraphics->renderForm( mWorldMap->getForm() );
	}

	std::cout << "... GAME OVER!!! ..." << endl;
}

int ExampleGame::init()
{
	initBindings();
	mGraphics->init();

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );
	mWorldMap->setForm( new OgreForm( "form" ) );

	addChild( mWorldMap );
}

