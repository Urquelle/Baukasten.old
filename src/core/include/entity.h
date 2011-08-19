#ifndef ENTITY_H
#define ENTITY_H

#include "global.h"
#include "object.h"

#include <list>
#include <string>

namespace Baukasten {
    namespace Core {
        class State;

        class BAUKASTEN_EXPORT Entity : public Object {
        public:
            Entity( const std::string& );
			Entity& operator=( const Entity& );
            bool operator==( const Entity& ) const;

            virtual ~Entity();

            void addState( State& );
            State* getState( const std::string& ) const;
			StateMap getStates() const;
            bool hasState( const std::string& ) const;

        protected:
            StateMap        mStates;
        };
    }
}

#endif // ENTITY_H

