#ifndef ACTION_LUA_6DRO5ZC8
#define ACTION_LUA_6DRO5ZC8

#include "model/Global"
#include "model/Action"

namespace Baukasten {
	class GameEntity;

	class BAUKASTEN_EXPORT ActionLua : public Action {
	public:
		ActionLua( GameEntity&, const string&, const string& );
		virtual ~ActionLua();

		virtual void doAction( GameEntity* );

	private:
		const string m_path;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LUA_6DRO5ZC8 */
