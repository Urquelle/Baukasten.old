#ifndef INC_ACTIONS_GW487EFJ
#define INC_ACTIONS_GW487EFJ

#include "global.h"
#include "abstract_manager.h"

namespace Baukasten {
	class Action;

	/*! \brief implements action container class.
	 *
	 * \ingroup action
	 *
	 * wrapps methods implemented in AbstractManager to limit the usage
	 * of this class to Action classes only.
	 */
	class BAUKASTEN_EXPORT ActionManager :
		protected virtual AbstractManager<Action> {
	public:

		/*! \brief constructor */
		ActionManager();

		/*! \brief destructor */
		virtual ~ActionManager();

		/*! \brief adds an Action object to the map.
		 *
		 * adds the given Action object to the map. Action::getId() is
		 * used as the key for the map.
		 *
		 * \param action Action object to insert.
		 * \sa addAction( const std::string&, Action* )
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
		void addAction( const std::string&, Action* );

		/*! \brief returns the Action object to the given id.
		 *
		 * returns the Action object to the given id, if the key
		 * is not in the map a NULL is returned.
		 *
		 * \param id key in the map under which the object was inserted.
		 * \return a pointer to the Action object if found, NULL otherwise.
		 */
		Action* getAction( const std::string& ) const;

		/*! \brief returns the map of objects. */
		ActionMap getActions() const;

		/*! \brief returns a list of currently active actions.
		 *
		 * actions that were invoked and still are in the
		 * execution queue are returned.
		 *
		 * \return ActionList actions in the execution queue.
		 */
		ActionList getInvokedActions() const;

		/*! \brief returns wheter the the key's present in the map.
		 *
		 * \return true if key found, false otherwise.
		 */
		bool hasAction( const std::string& ) const;

		/*! \brief put action into the execution queue.
		 *
		 * puts the action with the given id into the execution
		 * queue, with source object as its target.
		 *
		 * \param id id of the action.
		 */
		void invokeAction( const std::string& );

		/*! \brief put action into the execution queue.
		 *
		 * puts the action with the given id into the execution
		 * queue, with the given GameEntity object as its target.
		 *
		 * \param id id of the action.
		 * \param target target object.
		 */
		void invokeAction( const std::string&, GameEntity* );

		/*! \brief put action into the execution queue.
		 *
		 * puts the action with the given id into the execution
		 * queue, with the given GameEntityList as its targets.
		 *
		 * \param id id of the action.
		 * \param targets target objects.
		 */
		void invokeAction( const std::string&, GameEntityList );

		/*! \brief drop action from the execution queue.
		 *
		 * removes the action with the given id from the execution
		 * queue.
		 *
		 * \param id id of action.
		 */
		void dropAction( const std::string& );

	private:
		ActionList	mActionQueue;
	};
} /* Baukasten */

#endif /* end of include guard: INC_ACTIONS_GW487EFJ */
