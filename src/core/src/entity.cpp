#include "entity.h"
#include "state.h"

using namespace Baukasten::Core;

Entity::Entity( const std::string &id ) :
    mId( id )
{
}

Entity& Entity::operator=( const Entity &other )
{
	if ( this == &other )
		return *this;

	mId = other.getId();
	mStates = other.getStates();

	return *this;
}

bool Entity::operator==( const Entity &other ) const
{
    return ( mId == other.getId() );
}

Entity::~Entity()
{
}

const std::string Entity::getId() const
{
    return mId;
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

