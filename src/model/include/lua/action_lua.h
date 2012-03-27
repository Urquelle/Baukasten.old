#ifndef ACTION_LUA_6DRO5ZC8
#define ACTION_LUA_6DRO5ZC8

#include "model/Global"
#include "model/Action"

namespace Baukasten {
	class GameEntity;

	/*!
	 * \brief action class with lua binding.
	 *
	 * \ingroup model action
	 * \headerfile ActionLua "model/ActionLua"
	 *
	 * action class wich executes the given lua script. before the
	 * script is executed a couple of lua global variables are set.
	 *
	 * - source, being the source GameEntity and
	 *
	 * - action, being this very object.
	 */
	class BAUKASTEN_EXPORT ActionLua : public Action {
	public:

		/*!
		 * \brief constructor
		 *
		 * \param source GameEntity object that this action is bound to.
		 * \param id id of the action object.
		 * \param path path to the lua script file.
		 */
		ActionLua( GameEntity&, const string&, const string& );

		/*! \brief destructor */
		virtual ~ActionLua();

		/*!
		 * \brief executes the script.
		 *
		 * this method binds the source, target and action objects to lua
		 * context before executing the script.
		 *
		 * \param entity target GameEntity object.
		 */
		virtual void doAction( GameEntity* );

	private:
		const string m_path;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LUA_6DRO5ZC8 */
