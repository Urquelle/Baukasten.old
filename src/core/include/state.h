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

		virtual State* pack();

	protected:
		State*	mIntState;
	};
} /* Baukasten */

#endif // STATE_H

