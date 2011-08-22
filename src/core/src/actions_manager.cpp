#include "actions_manager.h"

#include "action.h"

using namespace Baukasten;

ActionsManager::ActionsManager()
{
}

ActionsManager::~ActionsManager()
{
}

void ActionsManager::addAction( Action *action )
{
	add( action );
}

void ActionsManager::addAction( const std::string &id, Action *action )
{
	add( id, action );
}

Action* ActionsManager::getAction( const std::string &id ) const
{
	return get( id );
}

ActionMap ActionsManager::getActions() const
{
	return getAll();
}

bool ActionsManager::hasAction( const std::string &id ) const
{
    return has( id );
}

void ActionsManager::invokeAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        mActionQueue.push_back( action );
    }
}

void ActionsManager::invokeAction( const std::string &id, GameEntity *target )
{
	if ( !target )
		return;

    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTarget( target );
        mActionQueue.push_back( action );
    }
}

void ActionsManager::invokeAction( const std::string &id, GameEntityList targets )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTargets( targets );
        mActionQueue.push_back( action );
    }
}

void ActionsManager::dropAction( const std::string &id )
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

void ActionsManager::runActions()
{
    ActionList::const_iterator it = mActionQueue.begin();
    while ( it != mActionQueue.end() )
        (*it++)->run();
}

