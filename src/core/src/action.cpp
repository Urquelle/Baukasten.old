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
    mTargets.erase( mTargets.begin(), mTargets.end() );
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

void Action::setTargets( EntityList &targets )
{
    mTargets = targets;
}

EntityList Action::getTargets()
{
	return mTargets;
}

void Action::run()
{
	// remove the action from the execution queue
	getSource()->dropAction( getId() );

	Entity *target = getTarget();

	if ( target ) {
		doAction( target );
		return;
	}

	EntityList targets = getTargets();
	if ( !targets.empty() ) {
		EntityList::iterator it = targets.begin();
		while( it != targets.end() ) {
			doAction( *it );
			++it;
		}
	}

	if ( !target && targets.empty() )
		doAction( getSource() );
}

