#include "city.h"

#include <generic_state.h>

using namespace Baukasten;

City::City( const string &id ) :
	GameEntity( id )
{
	addState( "state:visited", new StateInt( "state:visited", 0 ) );
	addState( "state:name", new StateString( "state:name", "<unknown>" ) );
}

City::~City()
{
}

