#ifndef ENTITY_TYPE_XJ90PEI
#define ENTITY_TYPE_XJ90PEI

#include "entity.h"
#include "global.h"
#include "states_manager.h"

namespace Baukasten {
	namespace Core {
		class BAUKASTEN_EXPORT EntityType :
			public Entity, public StatesManager {
		public:
			EntityType( const std::string& );
			virtual ~EntityType();

			void setParent( EntityType* );
			EntityType* getParent() const;

			void addChild( EntityType* );
			void removeChild( const EntityType* );

			State* getState( const std::string& ) const;
			State* getEntityState( const std::string& );

		private:
			EntityType*		mParent;
			EntityTypeList	mChildren;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: ENTITY_TYPE_XJ90PEI */
