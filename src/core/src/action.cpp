#include "action.h"
#include "game_entity.h"

using namespace Baukasten::Core;

Action::Action( GameEntity &source, const std::string &id ) :
    Entity( id ),
    mSource( &source ),
    mActive( false )
{
}

Action::~Action()
{
}

GameEntity* Action::getSource() const
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

void Action::setTarget( GameEntity *target )
{
	if ( target )
		mTarget = target;
}

GameEntity* Action::getTarget()
{
    return mTarget;
}

void Action::setTargets( GameEntityList &targets )
{
    mTargets = targets;
}

GameEntityList Action::getTargets()
{
	return mTargets;
}

void Action::run()
{
	// remove the action from the execution queue
	getSource()->dropAction( getId() );

	GameEntity *target = getTarget();

	if ( target ) {
		doAction( target );
		return;
	}

	GameEntityList targets = getTargets();
	if ( !targets.empty() ) {
		GameEntityList::iterator it = targets.begin();
		while( it != targets.end() ) {
			doAction( *it );
			++it;
		}
		return;
	}

	if ( !target && targets.empty() )
		doAction( getSource() );
}

