#ifndef ACTION_LUA_6DRO5ZC8
#define ACTION_LUA_6DRO5ZC8

#include "model/Global"

#include "model/Action"

#include <string>

namespace Baukasten {
	class GameEntity;

	class BAUKASTEN_EXPORT ActionLua : public Action {
	public:
		ActionLua( GameEntity&, const std::string&, const std::string& );
		virtual ~ActionLua();

		virtual void doAction( GameEntity* );

	private:
		const std::string	m_filePath;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_LUA_6DRO5ZC8 */
