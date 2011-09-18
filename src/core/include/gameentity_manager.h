#ifndef GAMEENTITY_MANAGER_BOBYOX91
#define GAMEENTITY_MANAGER_BOBYOX91

#include "global.h"

#include "abstract_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT GameEntityManager :
		protected virtual AbstractManager<GameEntity> {
	public:
		GameEntityManager();
		virtual ~GameEntityManager();

		void addGameEntity( GameEntity* );
		void addGameEntity( const std::string&, GameEntity* );
		GameEntity* getGameEntity( const std::string& ) const;
		AbstractManager<GameEntity>::TMap getGameEntities() const;
		bool hasGameEntity( const std::string& ) const;
		void removeGameEntity( const std::string& );
	};
} /* Baukasten */

#endif /* end of include guard: GAMEENTITY_MANAGER_BOBYOX91 */

