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
ActionManager::action( const std::string &id ) const
{
	return get( id );
}

ActionManager::TMap
ActionManager::actions() const
{
	return all();
}

list<Action*>
ActionManager::invokedActions() const
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
	Action *_action = action( id );

	if ( _action && !_action->isActive() ) {
		_action->clear();
		_action->setActive( true );
		mActionQueue.push_back( _action );

		_action->source()->onActionInvoked().emit(
			_action->source(),
			_action
		);
	}
}

void
ActionManager::invokeAction( const std::string &id, GameEntity *target )
{
	BK_ASSERT( target != 0, "target must not be 0" );
	Action *_action = action( id );

	if ( _action && !_action->isActive() ) {
		_action->clear();
		_action->setActive( true );
		_action->setTarget( target );
		mActionQueue.push_back( _action );

		_action->source()->onActionInvoked().emit(
			_action->source(),
			_action
		);
	}
}

void
ActionManager::invokeAction( const std::string &id, list<GameEntity*> targets )
{
	Action *_action = action( id );

	if ( _action && !_action->isActive() ) {
		_action->clear();
		_action->setActive( true );
		_action->setTargets( targets );
		mActionQueue.push_back( _action );

		_action->source()->onActionInvoked().emit(
			_action->source(),
			_action
		);
	}
}

void
ActionManager::dropAction( const std::string &id )
{
	Action *_action = action( id );

	if ( _action && _action->isActive() ) {
		_action->setActive( false );
		mActionQueue.erase(
			find_if( mActionQueue.begin(), mActionQueue.end(), [_action](Action *a) {
				return a == _action;
			})
		);
	}
}

