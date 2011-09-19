#ifndef FORM_H
#define FORM_H

#include "global.h"

#include "drawable.h"
#include "entity_manager.h"
#include "state_manager.h"

#include <string>

namespace Baukasten {
	class LogicalSpace;
	class VirtualSpace;

	class BAUKASTEN_EXPORT Form : public Drawable,
	public EntityManager, public StateManager {
	public:
		Form( const std::string& );
		virtual ~Form();

		void addToLSpace( GameEntity* );
		void removeFromLSpace( const std::string& );
		LogicalSpace* getLSpace() const;

		void addToVSpace( Drawable* );
		void removeFromVSpace( const std::string& );
		VirtualSpace* getVSpace() const;

		virtual void render();

	protected:
		shared_ptr<LogicalSpace> mLSpace;
		shared_ptr<VirtualSpace> mVSpace;
	};
}

#endif // FORM_H

