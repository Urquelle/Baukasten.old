#ifndef FORM_H
#define FORM_H

#include "global.h"
#include "renderable_entity.h"

namespace Baukasten
{
    namespace Core
    {
        class BAUKASTEN_EXPORT Form : public RenderableEntity
        {
        public:
            Form();
            virtual ~Form() = 0;
        };
    }
}

#endif // FORM_H

