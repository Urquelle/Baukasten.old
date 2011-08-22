#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "entity.h"

#include <string>

namespace Baukasten {
	class BAUKASTEN_EXPORT State : public Entity {
	public:
		State( const std::string& );
		virtual ~State();
	};
} /* Baukasten */

#endif // STATE_H

