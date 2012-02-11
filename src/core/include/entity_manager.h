#ifndef ENTITY_MANAGER_ZCJZL2J5
#define ENTITY_MANAGER_ZCJZL2J5

#include "global.h"

#include "generic_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT EntityManager :
		protected virtual GenericManager<Entity> {
	public:
		EntityManager();
		virtual ~EntityManager();

		void addEntity( Entity* );
		void addEntity( const std::string&, Entity* );
		Entity* entity( const std::string& ) const;
		TMap entities() const;
		bool hasEntity( const std::string& ) const;
		void removeEntity( const std::string& );
	};
} /* Baukasten */

#endif /* end of include guard: ENTITY_MANAGER_ZCJZL2J5 */
