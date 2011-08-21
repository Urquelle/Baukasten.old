#ifndef ENTITY_H
#define ENTITY_H

#include "global.h"

#include <string>

namespace Baukasten {
    namespace Core {
        class State;

        class BAUKASTEN_EXPORT Entity {
        public:
            Entity( const std::string& );
            virtual ~Entity();

			Entity& operator=( const Entity& );
            bool operator==( const Entity& ) const;

			const std::string& getId() const;

		private:
			std::string mId;
        };
    }
}

#endif // ENTITY_H

