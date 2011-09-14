#include "action_lambda.h"

#include "debug.h"

using namespace Baukasten;

ActionLambda::ActionLambda(
		GameEntity &source,
		const std::string &id,
		DoActionFunction *doActFunc,
		DoneFunction *doneFunc
		) :
	Action( source, id ),
	mDoAction( doActFunc ),
	mDone( doneFunc )
{
}

ActionLambda::~ActionLambda()
{
}

bool ActionLambda::done() const
{
	if ( !mDone )
		return Action::done();
	return (*mDone)( this );
}

void ActionLambda::doAction( GameEntity *entity )
{
	BK_ASSERT( mDoAction != 0, "function pointer must not be 0." );
	(*mDoAction)( this, entity );
}

