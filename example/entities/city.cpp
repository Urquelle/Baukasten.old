#include "city.h"

#include "forms/city_form.h"

#include <core_services.h>
#include <generic_state.h>

using namespace Baukasten;

City::City( const string &id ) :
	GameEntity( id )
{
	CoreServices *services = CoreServices::instance();

	addState( new StateInt( "state:visited", 0 ) );
	addState( new StateString( "state:name", "<unknown>" ) );
	addState( new StateString( "state:cityUp" ) );
	addState( new StateString( "state:cityRight" ) );
	addState( new StateString( "state:cityDown" ) );
	addState( new StateString( "state:cityLeft" ) );

	setForm( new CityForm( "form:city", services->getVideoService()) );
}

City::~City()
{
}

