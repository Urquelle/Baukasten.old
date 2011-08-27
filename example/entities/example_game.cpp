#include "actions/render_scene.h"
#include "example_game.h"
#include "forms/ogre_form.h"
#include "lua/bindings.h"
#include "world_map.h"

#include <action.h>
#include <form.h>
#include <generic_state.h>
#include <graphics_interface.h>
#include <igraphics.h>
#include <lua/action.h>

using namespace Baukasten;

ExampleGame::ExampleGame( const std::string &id ) :
	GameEntity( id )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );

	addAction( new ActionLua( *this, "updateState", "scripts/update_state.lua" ) );
	addAction( "renderScene", new RenderScene( *this ) );

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
    using namespace Baukasten;
    using namespace std;

	IGraphics *graphics = GraphicsInterface::instance();
	graphics->init();

	invokeAction( "renderScene" );

	// mainloop
	while ( keepRunning() ) {

		invokeAction( "updateState" );
		invokeAction( "processInput" );

		runActions();

		//mRoot->renderOneFrame();
	}
}

int ExampleGame::init()
{
	initBindings();

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );
	mWorldMap->setForm( new OgreForm( "form" ) );

	addChild( mWorldMap );
}

