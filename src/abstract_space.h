#ifndef ABSTRACT_SPACE_H
#define ABSTRACT_SPACE_H

#include "object.h"

#include <list>

namespace Eisenfaust
{
    class AbstractSpace
    {
    public:
        void append( const Object* );
        void clear();
    private:
        std::list<const Object*> m_entityList;
    };
}

#endif // ABSTRACT_SPACE_H

