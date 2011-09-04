#ifndef FORM_H
#define FORM_H

#include "global.h"

#include "drawable.h"
#include "entity_manager.h"
#include "object_manager.h"
#include "state_manager.h"

#include <string>

namespace Baukasten {
	class LogicalSpace;
	class VirtualSpace;

	class BAUKASTEN_EXPORT Form : public Drawable,
	public EntityManager, public ObjectManager, public StateManager {
	public:
		Form( const std::string& );
		virtual ~Form();

		void addToLSpace( Entity* );
		void removeFromLSpace( const std::string& );
		LogicalSpace* getLSpace() const;

		void addToVSpace( Drawable* );
		void removeFromVSpace( const std::string& );
		VirtualSpace* getVSpace() const;

		virtual void render();

	protected:
		LogicalSpace*	mLSpace;
		VirtualSpace*	mVSpace;
	};
}

#endif // FORM_H

