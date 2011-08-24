#ifndef ENTITY_TYPE_XJ90PEI
#define ENTITY_TYPE_XJ90PEI

#include "entity.h"
#include "global.h"
#include "state_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT EntityType :
		public Entity, public StateManager {
	public:
		EntityType( const std::string& );
		virtual ~EntityType();

		void setParent( EntityType* );
		EntityType* getParent() const;

		void addChild( EntityType* );
		void removeChild( const EntityType* );

		template<class T>
		T getState( const std::string &id ) const
		{
			T state = StateManager::getState<T>( id );

			if ( !state && mParent )
				state = mParent->getState<T>( id );

			return state;
		}

		State* getEntityState( const std::string& );

	private:
		EntityType*		mParent;
		EntityTypeList	mChildren;
	};
} /* Baukasten */

#endif /* end of include guard: ENTITY_TYPE_XJ90PEI */
