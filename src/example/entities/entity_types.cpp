#include "entity_types.h"
#include "actions/actions.h"

BasicClass::BasicClass( const std::string &id ) :
	EntityType( id ),
	mSex( new StateInt( "sex", 0 ) ),
	mMovement( new StateInt( "movement", 4 ) ),
	mJumpHeight( new StateInt( "jumpHeight", 3 ) ),
	mSpeed( new StateInt( "speed", 8 ) )
{
	addState( mSex );
	addState( mMovement );
	addState( mJumpHeight );
	addState( mSpeed );
}

BasicClass::~BasicClass()
{
}

