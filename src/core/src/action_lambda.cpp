#include "action_lambda.h"

#include "debug.h"

using namespace Baukasten;

ActionLambda::ActionLambda(
		GameEntity &source,
		const std::string &id,
		DoneFunction *doneFunc,
		DoActionFunction *doActFunc
		) :
	Action( source, id ),
	mDone( doneFunc ),
	mDoAction( doActFunc )
{
}

ActionLambda::~ActionLambda()
{
}

bool ActionLambda::done() const
{
	BK_ASSERT( mDone != 0, "function pointer must not be 0." );
	return (*mDone)( this );
}

void ActionLambda::doAction( GameEntity *entity )
{
	BK_ASSERT( mDoAction != 0, "function pointer must not be 0." );
	(*mDoAction)( this, entity );
}

