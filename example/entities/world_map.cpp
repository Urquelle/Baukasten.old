#include "world_map.h"

#include "basic_type.h"
#include "core_services.h"
#include "entities/unit.h"
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

WorldMap::~WorldMap()
{
}

