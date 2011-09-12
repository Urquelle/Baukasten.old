#include "world_map.h"

#include "core_services.h"
#include "forms/form2d.h"

#include <lua/action_lua.h>
#include <form.h>
#include <generic_state.h>

using namespace Baukasten;

GameEntity* createPointer()
{
	t_pos berlin = { 467, 338, 100 };
	t_pos mannheim = { 420, 410, 100 };

	CoreServices *services = CoreServices::instance();

	GameEntity *pointer = new GameEntity( "entity:pointer" );
	pointer->addState( new StateString( "state:currentCity", "berlin" ) );

	Form2d *form = new Form2d(
		"form:pointer",
		"media/1024x768/pointer.jpg",
		services->getVideoService()
	);

	form->setSize( { 45, 35 } );
	form->setPosition( berlin );

	pointer->setForm( form );

	return pointer;
}

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addState( new StateString( "state:currentCity", "berlin" ) );

	addAction( new ActionLua( *this, "moveRightOnMap", "scripts/move_right_on_map.lua" ) );
	addAction( new ActionLua( *this, "moveLeftOnMap", "scripts/move_left_on_map.lua" ) );

	CoreServices *services = CoreServices::instance();

	Form2d *wmForm = new Form2d(
		"form:worldmap",
		"media/1024x768/worldmap.jpg",
		services->getVideoService()
	);

	wmForm->setPosition( { 0, 0, 0 } );
	wmForm->setSize( { 1024, 768 } );

	setForm( wmForm );

	GameEntity *pointer = createPointer();
	wmForm->addToVSpace( pointer->getForm() );
	addChild( pointer );
}

WorldMap::~WorldMap()
{
}

