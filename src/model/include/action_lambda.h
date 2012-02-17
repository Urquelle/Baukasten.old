#ifndef ACTION_LAMBDA_A41U943N
#define ACTION_LAMBDA_A41U943N

#include "model/Global"
#include "model/Action"

#include <algorithm>

namespace Baukasten {
	typedef std::function<bool ( const Action* )> DoneFunction;
	typedef std::function<void ( Action*, GameEntity* )> DoActionFunction;

	class BAUKASTEN_EXPORT ActionLambda : public Action {
	public:
		ActionLambda( GameEntity&, const std::string&, DoActionFunction *doActFunc = 0, DoneFunction *doneFunc = 0 );
		virtual ~ActionLambda();

		bool done() const;
		void doAction( GameEntity* );

		void setDoActionFunction( DoActionFunction* );
		void setDoneFunction( DoneFunction* );

	private:
		DoActionFunction*	mDoAction;
		DoneFunction*		mDone;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LAMBDA_A41U943N */