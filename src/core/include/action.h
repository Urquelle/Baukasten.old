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
            Action( Entity&, const std::string& );
            virtual ~Action();

            Entity* getSource() const;
            void clear();
            bool isActive() const;
            void setActive( bool );

            void setTarget( Entity& );
            Entity* getTarget();

            void setTargets( EntityList& );
			EntityList getTargets();

			virtual void run();
            virtual void doAction( Entity* ) = 0;

        private:
            Entity*     mSource;
            Entity*     mTarget;
            EntityList  mTargets;
            bool        mActive;
        };
    } /* Core */
} /* Baukasten */

#endif /* end of include guard: ACTION_4GNSEOOP */
