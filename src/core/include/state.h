#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "entity.h"

namespace Baukasten
{
    namespace Core
    {
        class BAUKASTEN_EXPORT State : public Entity
        {
        public:
            State();
            virtual ~State();

        private:
            /* data */
        };
    } /* Core */
} /* Eisenfaust */

#endif // STATE_H

