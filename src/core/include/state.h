#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "entity.h"

#include <string>

namespace Baukasten {
    namespace Core {
        class BAUKASTEN_EXPORT State : public Entity {
        public:
            State( Entity& );
            State( Entity&, const std::string& );

            virtual ~State();

            const Entity* getParent() const;

        private:
            Entity*     mParent;
        };
    } /* Core */
} /* Baukasten */

#endif // STATE_H

