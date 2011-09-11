#include "world_map.h"

#include "core_services.h"
#include "forms/form2d.h"

#include <form.h>
#include <generic_state.h>

using namespace Baukasten;

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addState( new StateString( "state:currentCity", "berlin" ) );
	addState( new StateStringVector( "state:cities", { "berlin", "mannheim", "münchen" } ) );

	CoreServices *services = CoreServices::instance();

	Form2d *wmForm = new Form2d(
		"form:worldmap",
		"media/1024x768/worldmap.jpg",
		services->getVideoService()
	);

	wmForm->setPosition( { 0, 0, 0 } );
	wmForm->setSize( { 1024, 768 } );

	setForm( wmForm );
}

WorldMap::~WorldMap()
{
}

