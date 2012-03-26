#include "model/Action"

#include "model/GameEntity"

#include <algorithm>

using namespace Baukasten;
using namespace std;

Action::Action( GameEntity &source, const string &id ) :
	Entity( id ),
	m_source( &source ),
	m_target( 0 ),
	m_active( false )
{
}

Action::~Action()
{
}

GameEntity*
Action::source() const
{
	return m_source;
}

void
Action::clear()
{
	m_target = 0;
	m_targets.erase( m_targets.begin(), m_targets.end() );
}

bool
Action::isActive() const
{
	return m_active;
}

void
Action::setActive( bool active )
{
	m_active = active;
}

void
Action::setTarget( GameEntity *target )
{
	BK_ASSERT( target != 0, "target must not be 0." );
	m_target = target;
}

GameEntity*
Action::target()
{
	return m_target;
}

void
Action::setTargets( list<GameEntity*> &targets )
{
	m_targets = targets;
}

list<GameEntity*>
Action::targets()
{
	return m_targets;
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

