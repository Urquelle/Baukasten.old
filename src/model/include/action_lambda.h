#ifndef ACTION_LAMBDA_A41U943N
#define ACTION_LAMBDA_A41U943N

#include "model/Global"
#include "model/Action"

#include <algorithm>

namespace Baukasten {
	typedef function<bool ( const Action* )> DoneFunction;
	typedef function<void ( Action*, GameEntity* )> DoActionFunction;

	class BAUKASTEN_EXPORT ActionLambda : public Action {
	public:
		ActionLambda( GameEntity&, const string&, DoActionFunction *doActFunc = 0, DoneFunction *doneFunc = 0 );
		virtual ~ActionLambda();

		bool done() const;
		void doAction( GameEntity* );

		void setDoActionFunction( DoActionFunction* );
		void setDoneFunction( DoneFunction* );

	private:
		DoActionFunction*	m_doAction;
		DoneFunction*		m_done;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LAMBDA_A41U943N */
