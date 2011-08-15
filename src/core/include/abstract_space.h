#ifndef ABSTRACT_SPACE_H
#define ABSTRACT_SPACE_H

#include "global.h"
#include "entity.h"

#include <list>

namespace Baukasten {
    namespace Core {
        class BAUKASTEN_EXPORT AbstractSpace : public Entity {
        public:
            AbstractSpace() {}
            virtual ~AbstractSpace() {}

            void append( const Entity* );
            void clear();

        private:
            std::list<const Entity*> mEntityList;
        };
    }
}

#endif // ABSTRACT_SPACE_H

