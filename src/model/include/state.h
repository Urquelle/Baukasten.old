#ifndef STATE_H
#define STATE_H

#include "model/Entity"
#include "model/Global"

#include <sigc++/sigc++.h>

namespace Baukasten {
	class BAUKASTEN_EXPORT State : public Entity {
	public:
		State( const string& );
		virtual ~State();

		virtual State* pack();

		sigc::signal<void, State*> onChange();

	protected:
		State*	m_intState;

	private:
		sigc::signal<void, State*>	m_changed;
	};
} /* Baukasten */

#endif // STATE_H

