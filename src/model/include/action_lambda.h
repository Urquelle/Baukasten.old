#ifndef ACTION_LAMBDA_A41U943N
#define ACTION_LAMBDA_A41U943N

#include "model/Global"
#include "model/Action"

#include <algorithm>

namespace Baukasten {
	typedef function<bool ( const Action* )> DoneFunction;
	typedef function<void ( Action*, GameEntity* )> DoActionFunction;

	/*!
	 * \brief action lambda class.
	 *
	 * \ingroup model action
	 *
	 * \headerfile ActionLambda "model/ActionLambda"
	 *
	 * action lambda class implements the action entity in the given
	 * entity model. other than the plain action object this class
	 * can be given a block of code to each of its methods, them being:
	 *
	 * - doAction() and
	 *
	 * - done()
	 *
	 * thus, no subclassing has to take place, reducing the amount of
	 * files and effort.
	 */
	class BAUKASTEN_EXPORT ActionLambda : public Action {
	public:

		/*! \brief constructor
		 *
		 * constructor with one of its arguments being the lambda implementation
		 * of the doAction() method.
		 *
		 * \param source source GameEntity.
		 * \param id id of the action object.
		 * \param func lambda of the doAction() implementation.
		 */
		ActionLambda( GameEntity&, const string&, DoActionFunction );

		/*! \brief constructor
		 *
		 * constructor with one of its arguments being the lambda implementation
		 * of the doAction() method, and a simple bool as the implementation of
		 * the done() method.
		 *
		 * \param source source GameEntity.
		 * \param id id of the action object.
		 * \param func doActFunc lambda of the doAction() implementation.
		 * \param done boolean value for the done() method.
		 */
		ActionLambda( GameEntity&, const string&, DoActionFunction, bool );

		/*!
		 * \brief constructor
		 *
		 * constructor with one of its arguments being the lambda implementation
		 * of the doAction() method, and the other being another lambda
		 * implementation of the done() method.
		 *
		 * \param source source GameEntity.
		 * \param id id of the action object.
		 * \param doActFunc lambda of the doAction() implementation.
		 * \param doneFunc lambda of the done() implementation.
		 */
		ActionLambda( GameEntity&, const string&, DoActionFunction, DoneFunction );

		/*!
		 * \brief destructor
		 */
		virtual ~ActionLambda();

		/*!
		 * \brief reimplementation of the done() method.
		 *
		 * calls the given DoneFunction lambda.
		 */
		bool done() const;

		/*!
		 * \brief reimplementation of the doAction() method.
		 *
		 * calls the given DoActionFunction lambda.
		 */
		void doAction( GameEntity* );

		/*!
		 * \brief setter method for the doAction() implementation.
		 *
		 * sets the doAction() implementation.
		 *
		 * \param func implementation lambda.
		 */
		void setDoActionFunction( DoActionFunction );

		/*!
		 * \brief setter method for the done() implementation.
		 *
		 * sets the done() implementation.
		 *
		 * \param func implementation lambda.
		 */
		void setDoneFunction( DoneFunction );

	private:
		DoActionFunction  m_doAction;
		DoneFunction      m_done;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LAMBDA_A41U943N */
