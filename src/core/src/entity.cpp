#include "entity.h"
#include "state.h"
#include "action.h"

#include <cstdlib>
#include <ctime>

using namespace Baukasten::Core;

Entity::Entity()
{
    srand( time( NULL ) );
    Entity( "Entity_" + rand() );
}

Entity::Entity( const std::string &id ) :
    mId( id )
{
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
        mStateMap[ state.getId() ] = &state;
}

State* Entity::hasState( const std::string &stateId ) const
{
    StateMap::const_iterator it = mStateMap.find( stateId );
    return ( it == mStateMap.end() ) ? 0 : it->second;
}

void Entity::addAction( Action &action )
{
    if ( !hasAction( action.getId() ) )
        mActionMap[ action.getId() ] =  &action;
}

Action* Entity::hasAction( const std::string &actionId ) const
{
    ActionMap::const_iterator it = mActionMap.find( actionId );
    return ( it == mActionMap.end() ) ? 0 : it->second;
}

void Entity::invokeAction( const std::string &actionId ) const
{
    Action *action = hasAction( actionId );

    if ( action )
        action->doAction();
}

bool Entity::operator==( const Entity &other ) const
{
    return ( mId == other.getId() );
}

