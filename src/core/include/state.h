#ifndef STATE_H
#define STATE_H

#include "global.h"
#include "entity.h"

#include <string>

namespace Baukasten {
	class GameEntity;

	class BAUKASTEN_EXPORT State : public Entity {
	public:
		State( const std::string& );
		virtual ~State();

		void addTo( const GameEntity* );

	protected:
		std::list<const GameEntity*>	mEntities;
		bool					mIsLocked;
	};
} /* Baukasten */

#endif // STATE_H

