#include "core/Action"

#include "core/GameEntity"

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
Action::source() const
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
Action::target()
{
	return mTarget;
}

void
Action::setTargets( list<GameEntity*> &targets )
{
	mTargets = targets;
}

list<GameEntity*>
Action::targets()
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
	auto _source = source();

	// remove the action from the execution queue
	if ( done() )
		_source->dropAction( id() );

	auto _target = target();
	if ( _target ) {
		_source->onActionRun().emit( _source, this );
		doAction( _target );
		return;
	}

	auto _targets = targets();
	if ( !_targets.empty() ) {
		for_each( _targets.begin(), _targets.end(), [_source, this]( GameEntity* entity ) {
			_source->onActionRun().emit( _source, this );
			doAction( entity );
		});
		return;
	}

	if ( !_target && _targets.empty() ) {
		_source->onActionRun().emit( _source, this );
		doAction( _source );
	}
}

