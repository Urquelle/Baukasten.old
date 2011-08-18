#include "action.h"

using namespace Baukasten::Core;

Action::Action( Entity &source, const std::string &id ) :
    Entity( id ),
    mSource( &source ),
    mActive( false )
{
}

Action::~Action()
{
}

Entity* Action::getSource() const
{
    return mSource;
}

void Action::clear()
{
    mTarget = 0;
    mTargetList.erase( mTargetList.begin(), mTargetList.end() );
}

bool Action::isActive() const
{
    return mActive;
}

void Action::setActive( bool active )
{
    mActive = active;
}

void Action::setTarget( Entity &target )
{
    mTarget = &target;
}

Entity* Action::getTarget()
{
    return mTarget;
}

void Action::setTargetList( EntityList &targetList )
{
    mTargetList = targetList;
}

EntityList Action::getTargetList()
{
	return mTargetList;
}

void Action::doAction()
{
	// remove the action from the execution queue
	getSource()->dropAction( getId() );

	Entity *target = getTarget();

	if ( target ) {
		run( target );
		return;
	}

	EntityList targetList = getTargetList();
	if ( !targetList.empty() ) {
		EntityList::iterator it = targetList.begin();
		while( it != targetList.end() ) {
			run( *it );
			++it;
		}
	}

	if ( !target && targetList.empty() )
		run( getSource() );
}

