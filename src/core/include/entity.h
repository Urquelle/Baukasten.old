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
            Entity();
            Entity( const std::string& );

            virtual ~Entity();

            const std::string getId() const;

            void addState( State& );
            State* hasState(const std::string&) const;

            void addAction( Action& );
            Action* hasAction(const std::string&) const;
            void invokeAction( const std::string& ) const;

            bool operator==( const Entity& ) const;

        protected:
            std::string         mId;
            StateMap            mStateMap;
            ActionMap           mActionMap;
            Form*               mForm;
        };
    }
}

#endif // ENTITY_H

