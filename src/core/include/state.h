#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "object.h"

#include <string>

namespace Baukasten {
    namespace Core {
        class BAUKASTEN_EXPORT State : public Object {
        public:
            State( Entity&, const std::string& );
            virtual ~State();

            const Entity* getParent() const;

        private:
            Entity*     mParent;
        };
    } /* Core */
} /* Baukasten */

#endif // STATE_H

