#ifndef ENTITY_MANAGER_ZCJZL2J5
#define ENTITY_MANAGER_ZCJZL2J5

#include "model/GenericManager"
#include "model/Global"

namespace Baukasten {
	class BAUKASTEN_EXPORT EntityManager :
		protected virtual GenericManager<Entity> {
	public:
		EntityManager();
		virtual ~EntityManager();

		void addEntity( Entity* );
		void addEntity( const string&, Entity* );
		Entity* entity( const string& ) const;
		TMap entities() const;
		bool hasEntity( const string& ) const;
		void removeEntity( const string& );
	};
} /* Baukasten */

#endif /* end of include guard: ENTITY_MANAGER_ZCJZL2J5 */
