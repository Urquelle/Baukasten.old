#include "world_map.h"

#include "forms/ogre_form.h"

#include <form.h>
#include <generic_state.h>

using namespace Baukasten;

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addState( new StateString( "currentCity", "berlin" ) );
}

WorldMap::~WorldMap()
{
}

