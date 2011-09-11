#include "world_map.h"

#include "core_services.h"
#include "forms/worldmap_form.h"

#include <form.h>
#include <generic_state.h>

using namespace Baukasten;

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addState( new StateString( "state:currentCity", "berlin" ) );
	addState( new StateStringVector( "state:cities", { "berlin", "mannheim", "münchen" } ) );

	CoreServices *services = CoreServices::instance();

	setForm( new WorldMapForm(
		"form:worldmap",
		services->getVideoService()
	));
}

WorldMap::~WorldMap()
{
}

