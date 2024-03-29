#include "model/ActionManager"

#include "core/Debug"
#include "model/Action"
#include "model/GameEntity"

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
ActionManager::addAction( const string &id, Action *action )
{
	BK_ASSERT( action != 0, "action must not be 0" );
	add( id, action );
}

Action*
ActionManager::action( const string &id ) const
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
	return m_actionQueue;
}

bool
ActionManager::hasAction( const string &id ) const
{
	return has( id );
}

void
ActionManager::invokeAction( const string &id )
{
	Action *_action = action( id );

	if ( _action && !_action->isActive() ) {
		_action->clear();
		_action->setActive( true );
		m_actionQueue.push_back( _action );

		_action->source()->onActionInvoked().emit(
			_action->source(),
			_action
		);
	}
}

void
ActionManager::invokeAction( const string &id, GameEntity *target )
{
	BK_ASSERT( target != 0, "target must not be 0" );
	Action *_action = action( id );

	if ( _action && !_action->isActive() ) {
		_action->clear();
		_action->setActive( true );
		_action->setTarget( target );
		m_actionQueue.push_back( _action );

		_action->source()->onActionInvoked().emit(
			_action->source(),
			_action
		);
	}
}

void
ActionManager::invokeAction( const string &id, list<GameEntity*> targets )
{
	Action *_action = action( id );

	if ( _action && !_action->isActive() ) {
		_action->clear();
		_action->setActive( true );
		_action->setTargets( targets );
		m_actionQueue.push_back( _action );

		_action->source()->onActionInvoked().emit(
			_action->source(),
			_action
		);
	}
}

void
ActionManager::dropAction( const string &id )
{
	Action *_action = action( id );

	if ( _action && _action->isActive() ) {
		_action->setActive( false );
		m_actionQueue.erase(
			find_if( m_actionQueue.begin(), m_actionQueue.end(), [_action](Action *a) {
				return a == _action;
			})
		);
	}
}

