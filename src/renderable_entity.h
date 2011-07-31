#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "entity.h"
#include "global.h"

#include <tuple>

namespace Eisenfaust
{
    class RenderableEntity : public Entity
    {
    public:
        RenderableEntity();
        virtual ~RenderableEntity() = 0;
    private:
        t_coord m_coordinate;
    };
}

#endif // RENDERABLE_ENTITY_H
