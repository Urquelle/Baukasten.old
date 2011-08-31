#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "entity.h"

#include <sigc++/sigc++.h>

#include <string>

namespace Baukasten {
	class BAUKASTEN_EXPORT State : public Entity {
	public:
		State( const std::string& );
		virtual ~State();

		virtual State* pack();

		sigc::signal<void, State*> onChange();

	protected:
		State*	mIntState;

	private:
		sigc::signal<void, State*>	mChanged;
	};
} /* Baukasten */

#endif // STATE_H

