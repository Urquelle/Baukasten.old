#ifndef ABSTRACT_SPACE_H
#define ABSTRACT_SPACE_H

#include "entity.h"

#include <list>

namespace Eisenfaust
{
    class AbstractSpace : public Entity
    {
    public:
        AbstractSpace() {}
        virtual ~AbstractSpace() {}

        void append( const Entity* );
        void clear();

    private:
        std::list<const Entity*> m_entityList;
    };
}

#endif // ABSTRACT_SPACE_H

