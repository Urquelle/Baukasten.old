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
            virtual ~Entity();

            const std::string getId() const;

            void addState( State& );
            State* getState( const std::string& ) const;
            bool hasState( const std::string& ) const;

            void addAction( Action& );
            Action* getAction( const std::string& ) const;
            bool hasAction( const std::string& ) const;

            void invokeAction( const std::string& );
            void invokeAction( const std::string&, Entity& );
            void invokeAction( const std::string&, EntityList );

            void runActions();

            void setForm( Form& );
            Form* getForm() const;

            void addEntity( Entity& );
            bool hasEntity( const std::string& ) const;
            void removeEntity( const Entity& );

            bool operator==( const Entity& ) const;

        protected:
            std::string     mId;
            StateMap        mStateMap;
            ActionMap       mActionMap;
            ActionList      mActionQueue;
            Form*           mForm;
            EntityMap       mEntityMap;
        };
    }
}

#endif // ENTITY_H

