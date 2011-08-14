#ifndef FORM_H
#define FORM_H

#include "renderable_entity.h"

namespace Eisenfaust
{
    namespace Core
    {
        class Form : public RenderableEntity
        {
        public:
            Form();
            virtual ~Form() = 0;
        };
    }
}

#endif // FORM_H

