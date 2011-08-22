#ifndef ENTITY_MANAGER_ZCJZL2J5
#define ENTITY_MANAGER_ZCJZL2J5

#include "global.h"

#include "abstract_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT EntityManager : public AbstractManager<Entity> {
	public:
		EntityManager();
		virtual ~EntityManager();

		void addEntity( const std::string&, Entity* );
		Entity* getEntity( const std::string& ) const;
		EntityMap getEntities() const;
		bool hasEntity( const std::string& ) const;
		void removeEntity( const std::string& );
	};
} /* Baukasten */

#endif /* end of include guard: ENTITY_MANAGER_ZCJZL2J5 */
