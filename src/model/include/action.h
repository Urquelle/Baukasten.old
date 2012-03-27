#ifndef ACTION_4GNSEOOP
#define ACTION_4GNSEOOP

#include "model/Entity"
#include "model/Global"

#include <string>
#include <list>

namespace Baukasten {
	class GameEntity;

	/*! \brief action class.
	 *
	 * \ingroup model action
	 *
	 * \headerfile Action "model/Action"
	 *
	 * action class implements the action entity in britt l. hannah's
	 * object model. instances of this class operate on entitie's states
	 * and invoke other actions if so desired.
	 *
	 * all classes derived from this class have to implement the doAction()
	 * method in order for others to be able to invoke this action.
	 *
	 * in its default behaviour the action is executed once. it removes
	 * itself from the execution queue, so it isn't called the next time
	 * the runActions() method is called.
	 *
	 * the decision whether to remove itself from the execution queue is
	 * done in the done() method. the default implementation of this method
	 * returns true, hence the action removes itself from the queue the first
	 * time the doAction() method is called.
	 *
	 * for actions which have a more complicated decision process they have
	 * to reimplement the done() method.
	 */
	class BAUKASTEN_EXPORT Action : public Entity {
	public:

		/*! \brief constructor
		 *
		 * called on creation of an action class instance.
		 *
		 * \param source GameEntity object as action's source.
		 * \param id id of the action object.
		 */
		Action( GameEntity&, const string& );

		/*! \brief destructor */
		virtual ~Action();

		/*! \brief return action's source GameEntity
		 *
		 * every action can operate upon different GameEntity objects.
		 *
		 * 1. its source game entity, that the action is assigned to,
		 * 2. given target game entity
		 * 3. a list of target game entites
		 */
		GameEntity* source() const;

		/*! \brief clear action's target and targets objects
		 *
		 * clear the target pointer and empty the target list.
		 */
		void clear();

		/*! \brief getter method for action's active flag.
		 *
		 * \return true if action's active flag is set to true, false otherwise.
		 */
		bool isActive() const;

		/*! \brief setter method for action's active flag.
		 *
		 * \param active the active flag to set.
		 */
		void setActive( bool );

		/*! \brief sets the target object.
		 *
		 * set the target object for the action to operate on.
		 *
		 * \param target GameEntity* object as the target.
		 */
		void setTarget( GameEntity* );

		/*! \brief get target object.
		 *
		 * \return GameEntity object if set, 0 otherwise.
		 */
		GameEntity* target();

		/*! \brief set target objects.
		 *
		 * sets a list of targets to operate on.
		 *
		 * \param targets GameEntityList as a list of targets.
		 */
		void setTargets( list<GameEntity*>& );

		/*! \brief get the list of target objects.
		 *
		 * \return GameEntityList as a list of targets.
		 */
		list<GameEntity*> targets();

		/*! \brief returns bool whether or not the action should be dropped.
		 *
		 * holds the implementation of the decision whether or not
		 * the action should be dropped from the execution queue. default
		 * implementation returns true, so that the action is executed once and
		 * is then dropped.
		 *
		 * reimplement this method to modifie the behaviour.
		 */
		virtual bool done() const;

		/*! \brief run the action.
		 *
		 * default implementation goes through the possible target(s) and
		 * calls the doAction() method with the designated target. the target
		 * object is determined in the the following decision chain:
		 *
		 * - first the target object is checked.
		 *   if the target object is set, the doAction() method is called
		 *   with this object as the target and then the run() method is exited.
		 * - if the target object is not set, the targets list is the next
		 *   to be checked. the method goes through the list of targets and calls
		 *   the doAction() method for every target in the list. after this the
		 *   run() method is exited.
		 * - if neither the target nor the target list are set, call the doAction()
		 *   method with the source object as the target.
		 */
		virtual void run();

		/*! \brief method which every action deriving from this class has to implement.
		 *
		 * \param entity object to operate on.
		 */
		virtual void doAction( GameEntity *entity ) = 0;

	private:
		GameEntity*			m_source;
		GameEntity*			m_target;
		list<GameEntity*>	m_targets;
		bool				m_active;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_4GNSEOOP */
