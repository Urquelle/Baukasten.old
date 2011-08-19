#ifndef ENTITY_H
#define ENTITY_H

#include "global.h"

#include <list>
#include <string>

namespace Baukasten {
    namespace Core {
        class State;
        class Action;
        class Form;

        class BAUKASTEN_EXPORT Entity {
        public:
            Entity( const std::string& );
			Entity& operator=( const Entity& );
            bool operator==( const Entity& ) const;

            virtual ~Entity();

            const std::string getId() const;

            void addState( State& );
            State* getState( const std::string& ) const;
			StateMap getStates() const;
            bool hasState( const std::string& ) const;

            void addAction( Action& );
            Action* getAction( const std::string& ) const;
			ActionMap getActions() const;
            bool hasAction( const std::string& ) const;

            void invokeAction( const std::string& );
            void invokeAction( const std::string&, Entity& );
            void invokeAction( const std::string&, EntityList );

            void dropAction( const std::string& );

            void runActions();

            void setForm( Form& );
            Form* getForm() const;

            void addEntity( Entity& );
            bool hasEntity( const std::string& ) const;
			EntityMap getEntities() const;
            void removeEntity( const Entity& );

        protected:
            std::string     mId;
            StateMap        mStates;
            ActionMap       mActions;
            ActionList      mActionQueue;
            Form*           mForm;
            EntityMap       mEntities;
        };
    }
}

#endif // ENTITY_H

