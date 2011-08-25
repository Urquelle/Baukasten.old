#include "entity_types.h"

BasicClass::BasicClass( const std::string &id ) :
	EntityType( id )
{
	addState( new StateString( "name", "unknown" ) );

	addState( new StateInt( "hp", 10 ) );
	addState( new StateInt( "mp", 10 ) );
	addState( new StateInt( "exp", 0 ) );
	addState( new StateInt( "level", 1 ) );
}

BasicClass::~BasicClass()
{
}

