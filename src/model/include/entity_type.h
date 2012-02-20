#ifndef ENTITY_TYPE_XJ90PEI
#define ENTITY_TYPE_XJ90PEI

#include "model/Entity"
#include "model/Global"
#include "model/StateManager"

namespace Baukasten {
	class BAUKASTEN_EXPORT EntityType :
		public Entity, public StateManager {
	public:
		EntityType( const string& );
		virtual ~EntityType();

		void setParent( EntityType* );
		EntityType* parent() const;

		void addChild( EntityType* );
		void removeChild( const EntityType* );

		template<class T>
		T state( const string &id ) const
		{
			T state = StateManager::state<T>( id );

			if ( !state && m_parent )
				state = m_parent->state<T>( id );

			return state;
		}

		State* entityState( const string& );

	private:
		EntityType*		m_parent;
		EntityTypeList	m_children;
	};
} /* Baukasten */

#endif /* end of include guard: ENTITY_TYPE_XJ90PEI */
