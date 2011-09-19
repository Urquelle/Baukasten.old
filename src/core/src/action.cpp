#include "action.h"

#include "game_entity.h"

#include <algorithm>

using namespace Baukasten;
using namespace std;

Action::Action( GameEntity &source, const std::string &id ) :
	Entity( id ),
	mSource( &source ),
	mTarget( 0 ),
	mActive( false )
{
}

Action::~Action()
{
}

GameEntity*
Action::getSource() const
{
	return mSource;
}

void
Action::clear()
{
	mTarget = 0;
	mTargets.erase( mTargets.begin(), mTargets.end() );
}

bool
Action::isActive() const
{
	return mActive;
}

void
Action::setActive( bool active )
{
	mActive = active;
}

void
Action::setTarget( GameEntity *target )
{
	BK_ASSERT( target != 0, "target must not be 0." );
	mTarget = target;
}

GameEntity*
Action::getTarget()
{
	return mTarget;
}

void
Action::setTargets( GameEntityList &targets )
{
	mTargets = targets;
}

GameEntityList
Action::getTargets()
{
	return mTargets;
}

bool
Action::done() const
{
	return true;
}

void
Action::run()
{
	auto source = getSource();

	// remove the action from the execution queue
	if ( done() )
		source->dropAction( getId() );

	auto target = getTarget();
	if ( target ) {
		source->onActionRun().emit( source, this );
		doAction( target );
		return;
	}

	auto targets = getTargets();
	if ( !targets.empty() ) {
		for_each( targets.begin(), targets.end(), [source, this]( shared_ptr<GameEntity> entity ) {
			source->onActionRun().emit( source, this );
			doAction( entity.get() );
		});
		return;
	}

	if ( !target && targets.empty() ) {
		source->onActionRun().emit( source, this );
		doAction( getSource() );
	}
}

