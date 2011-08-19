#ifndef GAME_ENTITY_W1MJLLNE
#define GAME_ENTITY_W1MJLLNE

#include "entity.h"
#include "global.h"

namespace Baukasten {
	namespace Core {
		class EntityType;
		class Form;

		class BAUKASTEN_EXPORT GameEntity : public Entity {
		public:
			GameEntity( const std::string& );
			virtual ~GameEntity();

			void setType( EntityType& );
			EntityType* getType() const;

            void addAction( Action& );
            Action* getAction( const std::string& ) const;
			ActionMap getActions() const;
            bool hasAction( const std::string& ) const;

            void invokeAction( const std::string& );
            void invokeAction( const std::string&, GameEntity& );
            void invokeAction( const std::string&, GameEntityList );

            void dropAction( const std::string& );

            void runActions();

            void setForm( Form& );
            Form* getForm() const;

            void addEntity( GameEntity& );
            bool hasEntity( const std::string& ) const;
			GameEntityMap getEntities() const;
            void removeEntity( const GameEntity& );

		private:
			EntityType*		mType;
            ActionMap       mActions;
            ActionList      mActionQueue;
            Form*           mForm;
            GameEntityMap	mEntities;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: GAME_ENTITY_W1MJLLNE */
