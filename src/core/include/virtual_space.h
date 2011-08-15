#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "global.h"
#include "abstract_space.h"

namespace Eisenfaust
{
    namespace Core
    {
        class RenderableEntity;

        class EF_EXPORT VirtualSpace : public AbstractSpace
        {
        public:
            VirtualSpace();
            virtual ~VirtualSpace();

            void append( const RenderableEntity* );
        };
    }
}

#endif // VIRTUAL_SPACE_H

