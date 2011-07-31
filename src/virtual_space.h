#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "abstract_space.h"

namespace Eisenfaust
{
    class RenderableEntity;

    class VirtualSpace : public AbstractSpace
    {
    public:
        VirtualSpace();
        virtual ~VirtualSpace();

        void append( const RenderableEntity* );
    };
}

#endif // VIRTUAL_SPACE_H

