#include "core/ActionManager"

#include "core/Action"
#include "core/Debug"
#include "core/GameEntity"

#include <algorithm>

using namespace Baukasten;
using namespace std;

ActionManager::ActionManager()
{
}

ActionManager::~ActionManager()
{
}

void
ActionManager::addAction( Action *action )
{
	BK_ASSERT( action != 0, "action must not be 0" );
	add( action );
}

void
ActionManager::addAction( const std::string &id, Action *action )
{
	BK_ASSERT( action != 0, "action must not be 0" );
	add( id, action );
}

Action*
ActionManager::getAction( const std::string &id ) const
{
	return get( id );
}

ActionManager::TMap
ActionManager::getActions() const
{
	return getAll();
}

list<Action*>
ActionManager::getInvokedActions() const
{
	return mActionQueue;
}

bool
ActionManager::hasAction( const std::string &id ) const
{
	return has( id );
}

void
ActionManager::invokeAction( const std::string &id )
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

void
ActionManager::invokeAction( const std::string &id, GameEntity *target )
{
	BK_ASSERT( target != 0, "target must not be 0" );
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

void
ActionManager::invokeAction( const std::string &id, list<GameEntity*> targets )
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

void
ActionManager::dropAction( const std::string &id )
{
	Action *action = getAction( id );

	if ( action && action->isActive() ) {
		action->setActive( false );
		mActionQueue.erase(
			find_if( mActionQueue.begin(), mActionQueue.end(), [action](Action *a) {
				return a == action;
			})
		);
	}
}

