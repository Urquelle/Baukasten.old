#ifndef GAME_ENTITY_W1MJLLNE
#define GAME_ENTITY_W1MJLLNE

#include "global.h"

#include "action_manager.h"
#include "entity.h"
#include "entity_type.h"
#include "state_manager.h"

namespace Baukasten {
	class EntityType;
	class Form;

	class BAUKASTEN_EXPORT GameEntity : public Entity,
		public ActionManager, public StateManager {
	public:
		GameEntity( const std::string& );
		virtual ~GameEntity();

		void setType( EntityType* );
		EntityType* getType() const;

		void setForm( Form* );
		Form* getForm() const;

		bool hasState( const std::string& ) const;

		template<class T>
		T getState( const std::string &id ) const
		{
			T state = StateManager::getState<T>( id );

			if ( !state && getType() ) {
				state = getType()->getState<T>( id );
				state->addTo( this );
			}

			return state;
		}

		void addChild( GameEntity* );
		void removeChild( const std::string& );

		void setParent( GameEntity* );
		GameEntity* getParent() const;

		virtual void runActions();

	private:
		EntityType*		mType;
		Form*           mForm;
		GameEntityMap	mChildren;
		GameEntity*		mParent;
	};
} /* Baukasten */

#endif /* end of include guard: GAME_ENTITY_W1MJLLNE */

