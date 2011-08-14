#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "entity.h"
#include "global.h"

#include <tuple>

namespace Eisenfaust
{
    namespace Core
    {
        class RenderableEntity : public Entity
        {
        public:
            RenderableEntity() {}
            virtual ~RenderableEntity() {}

            void setPosition( const t_pos );
            void setPitch( const float );
            void setYaw( const float );
            void setRoll( const float );
            void setScale( const float );

        protected:
            // position of the object
            t_pos   mPosition;

            // rotation around the x-axis
            float   mPitch;

            // rotation around the y-axis
            float   mYaw;

            // rotation around the z-axis
            float   mRoll;

            // scaling factor of the object
            float   mScale;
        };
    }
}

#endif // RENDERABLE_ENTITY_H
