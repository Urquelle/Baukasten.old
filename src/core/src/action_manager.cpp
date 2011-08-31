#include "action_manager.h"

#include "action.h"
#include "game_entity.h"

using namespace Baukasten;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

void ActionManager::addAction( Action *action )
{
	add( action );
}

void ActionManager::addAction( const std::string &id, Action *action )
{
	add( id, action );
}

Action* ActionManager::getAction( const std::string &id ) const
{
	return get( id );
}

ActionMap ActionManager::getActions() const
{
	return getAll();
}

ActionList ActionManager::getInvokedActions() const
{
	return mActionQueue;
}

bool ActionManager::hasAction( const std::string &id ) const
{
    return has( id );
}

void ActionManager::invokeAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        mActionQueue.push_back( action );

		action->getSource()->onActionInvoked().emit(
			action->getSource(),
			action
		);
    }
}

void ActionManager::invokeAction( const std::string &id, GameEntity *target )
{
	if ( !target )
		return;

    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTarget( target );
        mActionQueue.push_back( action );

		action->getSource()->onActionInvoked().emit(
			action->getSource(),
			action
		);
    }
}

void ActionManager::invokeAction( const std::string &id, GameEntityList targets )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
		action->clear();
        action->setActive( true );
        action->setTargets( targets );
        mActionQueue.push_back( action );

		action->getSource()->onActionInvoked().emit(
			action->getSource(),
			action
		);
    }
}

void ActionManager::dropAction( const std::string &id )
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

