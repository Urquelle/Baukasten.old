#include "entity.h"
#include "state.h"
#include "action.h"
#include "form.h"

using namespace Baukasten::Core;

Entity::Entity( const std::string &id ) :
    mId( id ),
	mForm( 0 )
{
}

Entity& Entity::operator=( const Entity &other )
{
	if ( this == &other )
		return *this;

	mId = other.getId();
	mStates = other.getStates();
	mActions = other.getActions();
	mEntities = other.getEntities();
	mForm = other.getForm();

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

void Entity::addAction( Action &action )
{
    if ( !hasAction( action.getId() ) )
        mActions[ action.getId() ] =  &action;
}

Action* Entity::getAction( const std::string &id ) const
{
    ActionMap::const_iterator it = mActions.find( id );
    return ( it == mActions.end() ) ? 0 : it->second;
}

ActionMap Entity::getActions() const
{
	return mActions;
}

bool Entity::hasAction( const std::string &id ) const
{
    ActionMap::const_iterator it = mActions.find( id );
    return ( it != mActions.end() );
}

void Entity::invokeAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        mActionQueue.push_back( action );
    }
}

void Entity::invokeAction( const std::string &id, Entity &target )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTarget( target );
        mActionQueue.push_back( action );
    }
}

void Entity::invokeAction( const std::string &id, EntityList targetList )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTargetList( targetList );
        mActionQueue.push_back( action );
    }
}

void Entity::dropAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && action->isActive() ) {
		action->setActive( false );
        ActionList::iterator it = mActionQueue.begin();

        while ( it != mActionQueue.end() ) {
            if ( *it == action ) {
                mActionQueue.erase( it );
                break;
            }
			it++;
        }
    }
}

void Entity::runActions()
{
    ActionList::const_iterator it = mActionQueue.begin();
    while ( it != mActionQueue.end() )
        (*it++)->doAction();
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
        mEntities[ entity.getId() ] =  &entity;
}

bool Entity::hasEntity( const std::string &id ) const
{
    EntityMap::const_iterator it = mEntities.find( id );
    return ( it == mEntities.end() );
}

EntityMap Entity::getEntities() const
{
	return mEntities;
}

void Entity::removeEntity( const Entity &entity )
{
}

