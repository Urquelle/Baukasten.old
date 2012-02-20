#include "model/ActionLambda"

#include "core/Debug"

using namespace Baukasten;

ActionLambda::ActionLambda(
		GameEntity &source,
		const std::string &id,
		DoActionFunction *doActFunc,
		DoneFunction *doneFunc
		) :
	Action( source, id ),
	m_doAction( doActFunc ),
	m_done( doneFunc )
{
}

ActionLambda::~ActionLambda()
{
}

void
ActionLambda::setDoActionFunction( DoActionFunction *func )
{
	BK_ASSERT( func != 0, "function pointer must not be 0." );
	m_doAction = func;
}

void
ActionLambda::setDoneFunction( DoneFunction *func )
{
	BK_ASSERT( func != 0, "function pointer must not be 0." );
	m_done = func;
}

bool
ActionLambda::done() const
{
	if ( !m_done )
		return Action::done();
	return (*m_done)( this );
}

void
ActionLambda::doAction( GameEntity *entity )
{
	BK_ASSERT( m_doAction != 0, "function pointer must not be 0." );
	(*m_doAction)( this, entity );
}

