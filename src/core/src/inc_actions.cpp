#include "inc_actions.h"

#include "action.h"

using namespace Baukasten::Core;

IncActions::IncActions()
{
}

IncActions::~IncActions()
{
}

void IncActions::addAction( Action *action )
{
    if ( action && !hasAction( action->getId() ) )
        mActions[ action->getId() ] =  action;
}

Action* IncActions::getAction( const std::string &id ) const
{
    ActionMap::const_iterator it = mActions.find( id );
    return ( it == mActions.end() ) ? 0 : it->second;
}

ActionMap IncActions::getActions() const
{
	return mActions;
}

bool IncActions::hasAction( const std::string &id ) const
{
    ActionMap::const_iterator it = mActions.find( id );
    return ( it != mActions.end() );
}

void IncActions::invokeAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        mActionQueue.push_back( action );
    }
}

void IncActions::invokeAction( const std::string &id, GameEntity *target )
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

void IncActions::invokeAction( const std::string &id, GameEntityList targets )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTargets( targets );
        mActionQueue.push_back( action );
    }
}

void IncActions::dropAction( const std::string &id )
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

void IncActions::runActions()
{
    ActionList::const_iterator it = mActionQueue.begin();
    while ( it != mActionQueue.end() )
        (*it++)->run();
}

