#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "abstract_space.h"

namespace Eisenfaust
{
    class RenderableObject;

    class VirtualSpace : public AbstractSpace
    {
    public:
        VirtualSpace();
        virtual ~VirtualSpace();

        void append( const RenderableObject* );
    };
}

#endif // VIRTUAL_SPACE_H

