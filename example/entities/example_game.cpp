#include "actions/render_scene.h"
#include "basic_type.h"
#include "example_game.h"
#include "forms/world_map_form.h"
#include "unit.h"
#include "lua/bindings.h"
#include "world_map.h"

#include <action.h>
#include <generic_state.h>
#include <graphics_interface.h>
#include <igraphics.h>
#include <lua/action.h>

#include <OGRE/Ogre.h>

#include <iostream>
#include <cstdlib>

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
	//init();
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
	mWorldMap->setForm( new WorldMapForm( "form", mRoot ) );

	addChild( mWorldMap );

	BasicType *type = new BasicType( "basic" );

    Unit *sanchez = new Unit( "sanchez" );
    Unit *gomez = new Unit( "gomez" );
	Unit *ramirez = new Unit( "ramirez" );

	sanchez->setType( type );
	gomez->setType( type );
	ramirez->setType( type );

	sanchez->setName( sanchez->getId() );
	gomez->setName( gomez->getId() );
	ramirez->setName( ramirez->getId() );

	addChild( sanchez );
	addChild( gomez );
	addChild( ramirez );

	GameEntityList targets;

	targets.push_back( gomez );
	targets.push_back( ramirez );

	sanchez->invokeAction( "hit", targets );
}

