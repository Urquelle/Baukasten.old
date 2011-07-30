#ifndef RENDERABLE_OBJECT_H
#define RENDERABLE_OBJECT_H

#include "object.h"
#include "global.h"

#include <tuple>

namespace Eisenfaust
{
    class RenderableObject : public Object
    {
    public:
        RenderableObject();
        virtual ~RenderableObject() = 0;
    private:
        t_coord m_coordinate;
    };
}

#endif // RENDERABLE_OBJECT_H
