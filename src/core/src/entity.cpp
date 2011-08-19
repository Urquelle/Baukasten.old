#include "entity.h"
#include "state.h"

using namespace Baukasten::Core;

Entity::Entity( const std::string &id ) :
	Object( id )
{
}

Entity& Entity::operator=( const Entity &other )
{
	if ( this == &other )
		return *this;

	mStates = other.getStates();

	return *this;
}

Entity::~Entity()
{
}

void Entity::addState( State &state )
{
    if ( !hasState( state.getId() ) )
        mStates[ state.getId() ] = &state;
}

State* Entity::getState( const std::string &id ) const
{
    StateMap::const_iterator it = mStates.find( id );
    return ( it == mStates.end() ) ? 0 : it->second;
}

StateMap Entity::getStates() const
{
	return mStates;
}

bool Entity::hasState( const std::string &id ) const
{
    StateMap::const_iterator it = mStates.find( id );
    return ( it != mStates.end() );
}

