#ifndef ACTION_LAMBDA_A41U943N
#define ACTION_LAMBDA_A41U943N

#include "global.h"

#include "action.h"

#include <algorithm>

namespace Baukasten {
	typedef std::function<bool ( const Action* )> DoneFunction;
	typedef std::function<void ( Action*, GameEntity* )> DoActionFunction;

	class ActionLambda : public Action {
	public:
		ActionLambda( GameEntity&, const std::string&, DoneFunction*, DoActionFunction* );
		virtual ~ActionLambda();

		bool done() const;
		void doAction( GameEntity* );

	private:
		DoneFunction*		mDone;
		DoActionFunction*	mDoAction;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LAMBDA_A41U943N */
