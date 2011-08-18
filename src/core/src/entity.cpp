#include "entity.h"
#include "state.h"
#include "action.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace Baukasten::Core;

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

State* Entity::getState( const std::string &stateId ) const
{
    StateMap::const_iterator it = mStateMap.find( stateId );
    return ( it == mStateMap.end() ) ? 0 : it->second;
}

bool Entity::hasState( const std::string &stateId ) const
{
    StateMap::const_iterator it = mStateMap.find( stateId );
    return ( it == mStateMap.end() );
}

void Entity::addAction( Action &action )
{
    if ( !hasAction( action.getId() ) )
        mActionMap[ action.getId() ] =  &action;
}

Action* Entity::getAction( const std::string &actionId ) const
{
    ActionMap::const_iterator it = mActionMap.find( actionId );
    return ( it == mActionMap.end() ) ? 0 : it->second;
}

bool Entity::hasAction( const std::string &actionId ) const
{
    ActionMap::const_iterator it = mActionMap.find( actionId );
    return ( it == mActionMap.end() );
}

void Entity::invokeAction( const std::string &actionId ) const
{
    if ( !hasAction( actionId ) )
        return;

    Action *action = getAction( actionId );

    if ( action )
        action->doAction();
}

void Entity::setForm( Form &form )
{
    mForm = &form;
}

Form* Entity::getForm() const
{
    return mForm;
}

void Entity::addEntity( Entity &entity )
{
    if ( !hasEntity( entity.getId() ) )
        mEntityMap[ entity.getId() ] =  &entity;
}

bool Entity::hasEntity( const std::string &id ) const
{
    EntityMap::const_iterator it = mEntityMap.find( id );
    return ( it == mEntityMap.end() );
}

void Entity::removeEntity( const Entity &entity )
{
}

bool Entity::operator==( const Entity &other ) const
{
    return ( mId == other.getId() );
}

