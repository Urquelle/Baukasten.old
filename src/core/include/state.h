#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "entity.h"

#include <string>

namespace Baukasten {
	namespace Core {
		class BAUKASTEN_EXPORT State : public Entity {
		public:
			State( const std::string& );
			virtual ~State();
		};
	} /* Core */
} /* Baukasten */

#endif // STATE_H

