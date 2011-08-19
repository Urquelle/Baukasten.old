#include "entity_types.h"
#include "actions.h"

SquireClass::SquireClass( const std::string &id ) :
	EntityType( id ),
	mSex( new StateInt( "sex", 0 ) ),
	mMovement( new StateInt( "movement", 4 ) ),
	mJumpHeight( new StateInt( "jumpHeight", 3 ) ),
	mSpeed( new StateInt( "speed", 8 ) )
{
}

SquireClass::~SquireClass()
{
}

