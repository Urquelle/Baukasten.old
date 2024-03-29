#ifndef INC_ACTIONS_GW487EFJ
#define INC_ACTIONS_GW487EFJ

#include "model/Global"
#include "model/GenericManager"

namespace Baukasten {
	class Action;

	/*!
	 * \ingroup model
	 * @{
	 *
	 * \addtogroup action
	 * @{
	 *
	 * \class ActionManager
	 * \headerfile ActionManager "model/ActionManager"
	 * \brief implements action container class.
	 *
	 * wrapps methods implemented in GenericManager to limit the usage
	 * of this class to Action classes only.
	 */
	class BAUKASTEN_EXPORT ActionManager :
		protected virtual GenericManager<Action> {
	public:

		/*! \brief constructor */
		ActionManager();

		/*! \brief destructor */
		virtual ~ActionManager();

		/*! \brief adds an Action object to the map.
		 *
		 * adds the given Action object to the map. Action::id() is
		 * used as the key for the map.
		 *
		 * \param action Action object to insert.
		 * \sa addAction( const string&, Action* )
		 */
		void addAction( Action* );

		/*! \brief adds an Action object to the map.
		 *
		 * adds the given Action object to the map. the given id
		 * is used as the key for the map.
		 *
		 * \param action Action object to insert.
		 * \param id string which is used as the map key.
		 */
		void addAction( const string&, Action* );

		/*! \brief returns the Action object to the given id.
		 *
		 * returns the Action object to the given id, if the key
		 * is not in the map a NULL is returned.
		 *
		 * \param id key in the map under which the object was inserted.
		 * \return a pointer to the Action object if found, NULL otherwise.
		 */
		Action* action( const string& ) const;

		/*! \brief returns the map of objects. */
		TMap actions() const;

		/*! \brief returns a list of currently active actions.
		 *
		 * actions that were invoked and still are in the
		 * execution queue are returned.
		 *
		 * \return ActionList actions in the execution queue.
		 */
		list<Action*> invokedActions() const;

		/*! \brief returns wheter the the key's present in the map.
		 *
		 * \return true if key found, false otherwise.
		 */
		bool hasAction( const string& ) const;

		/*! \brief put action into the execution queue.
		 *
		 * puts the action with the given id into the execution
		 * queue, with source object as its target.
		 *
		 * \param id id of the action.
		 */
		void invokeAction( const string& );

		/*! \brief put action into the execution queue.
		 *
		 * puts the action with the given id into the execution
		 * queue, with the given GameEntity object as its target.
		 *
		 * \param id id of the action.
		 * \param target target object.
		 */
		void invokeAction( const string&, GameEntity* );

		/*! \brief put action into the execution queue.
		 *
		 * puts the action with the given id into the execution
		 * queue, with the given GameEntityList as its targets.
		 *
		 * \param id id of the action.
		 * \param targets target objects.
		 */
		void invokeAction( const string&, list<GameEntity*> );

		/*! \brief drop action from the execution queue.
		 *
		 * removes the action with the given id from the execution
		 * queue.
		 *
		 * \param id id of action.
		 */
		void dropAction( const string& );

	private:
		list<Action*> m_actionQueue;
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: INC_ACTIONS_GW487EFJ */
