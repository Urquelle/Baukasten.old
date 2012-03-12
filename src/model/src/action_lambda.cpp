#include "model/ActionLambda"

#include "core/Debug"

using namespace Baukasten;

ActionLambda::ActionLambda( GameEntity &source,
		const string &id, DoActionFunction func ) :
	Action( source, id ),
	m_doAction( func )
{
	m_done = ([]( const Action* ) {
		return true;
	});
}

ActionLambda::ActionLambda( GameEntity &source,
		const string &id, DoActionFunction func, bool done ) :
	Action( source, id ),
	m_doAction( func )
{
	m_done = ([done]( const Action* ) {
		return done;
	});
}

ActionLambda::ActionLambda( GameEntity &source,
		const string &id, DoActionFunction doActFunc,
		DoneFunction doneFunc ) :
	Action( source, id ),
	m_doAction( doActFunc ),
	m_done( doneFunc )
{
}

ActionLambda::~ActionLambda()
{
}

void
ActionLambda::setDoActionFunction( DoActionFunction func )
{
	m_doAction = func;
}

void
ActionLambda::setDoneFunction( DoneFunction func )
{
	m_done = func;
}

bool
ActionLambda::done() const
{
	if ( !m_done )
		return Action::done();
	return m_done( this );
}

void
ActionLambda::doAction( GameEntity *entity )
{
	m_doAction( this, entity );
}

