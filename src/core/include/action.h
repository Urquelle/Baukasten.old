#ifndef ACTION_4GNSEOOP
#define ACTION_4GNSEOOP

#include "global.h"
#include "entity.h"

#include <string>
#include <list>

namespace Baukasten {
    namespace Core {
        class BAUKASTEN_EXPORT Action : public Entity {
        public:
            Action( Entity& );
            Action( Entity&, const std::string& );

            virtual ~Action();

            const Entity* getParent() const;

            virtual void doAction() = 0;
            virtual void doAction( Entity& );
            virtual void doAction( std::list<Entity*> );

        private:
            Entity*     mParent;
        };
    } /* Core */
} /* Baukasten */

#endif /* end of include guard: ACTION_4GNSEOOP */
