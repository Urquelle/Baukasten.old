#ifndef ACTION_LUA_6DRO5ZC8
#define ACTION_LUA_6DRO5ZC8

#include "global.h"
#include "action.h"

class lua_State;

namespace Baukasten {
	namespace Core {
		class GameEntity;

		class BAUKASTEN_EXPORT ActionLua : public Action {
		public:
			ActionLua( GameEntity&, const std::string&, const std::string& );
			virtual ~ActionLua();

			virtual void doAction( GameEntity* );

		private:
			const std::string	mFilePath;
			lua_State*			mL;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: ACTION_LUA_6DRO5ZC8 */
