#ifndef GAME_ENTITY_W1MJLLNE
#define GAME_ENTITY_W1MJLLNE

#include "global.h"

#include "actions_manager.h"
#include "entity.h"
#include "objects_manager.h"
#include "states_manager.h"

namespace Baukasten {
	namespace Core {
		class EntityType;
		class Form;

		class BAUKASTEN_EXPORT GameEntity :
			public Entity, public ActionsManager,
			public StatesManager, public ObjectsManager {
		public:
			GameEntity( const std::string& );
			virtual ~GameEntity();

			void setType( EntityType* );
			EntityType* getType() const;

            void setForm( Form* );
            Form* getForm() const;

            void addEntity( const std::string&, GameEntity* );
            bool hasEntity( const std::string& ) const;
			GameEntityMap getEntities() const;
            void removeEntity( const GameEntity* );

			bool hasState( const std::string& ) const;
			State* getState( const std::string& ) const;

		private:
			EntityType*		mType;
            Form*           mForm;
            GameEntityMap	mEntities;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: GAME_ENTITY_W1MJLLNE */

