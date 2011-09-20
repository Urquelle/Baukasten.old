#include "city.h"

#include "forms/city_form.h"

#include <core_services.h>
#include <generic_state.h>

using namespace Baukasten;

City::City( const string &id ) :
	GameEntity( id )
{
	CoreServices *services = CoreServices::instance();

	addState( "state:visited", new StateInt( "state:visited", 0 ) );
	addState( "state:name", new StateString( "state:name", "<unknown>" ) );

	CityForm *form = new CityForm(
		"form:city",
		services->getVideoService()
	);

	form->addState( "state:mode", new StateInt( "state:mode", 0 ) );

	setForm( form );
}

City::~City()
{
}

