#include "world_map.h"

#include "core_services.h"
#include "forms/worldmap_form.h"

#include <form.h>
#include <generic_state.h>

using namespace Baukasten;

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addState( new StateString( "currentCity", "berlin" ) );

	CoreServices *services = CoreServices::instance();

	setForm( new WorldMapForm(
		"form:worldmap",
		services->getVideoService()
	));
}

WorldMap::~WorldMap()
{
}

