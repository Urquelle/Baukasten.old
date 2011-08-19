#ifndef ENTITY_H
#define ENTITY_H

#include "global.h"

#include <list>
#include <string>

namespace Baukasten {
    namespace Core {
        class State;

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

        protected:
            std::string     mId;
            StateMap        mStates;
        };
    }
}

#endif // ENTITY_H

