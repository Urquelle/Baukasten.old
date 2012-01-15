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
	class IGraphics;

	class BAUKASTEN_EXPORT Form : public Drawable,
	public EntityManager, public StateManager {
	public:
		Form( const std::string&, IGraphics *graphics = 0 );
		virtual ~Form();

		void addToLSpace( GameEntity* );
		void addToLSpace( const string&, GameEntity* );
		void removeFromLSpace( const std::string& );
		LogicalSpace* getLSpace() const;

		void addToVSpace( Form* );
		void addToVSpace( const string&, Form* );
		void removeFromVSpace( const std::string& );
		VirtualSpace* getVSpace() const;

		virtual void draw();
		virtual void render();

	protected:
		IGraphics *getGraphics() const;

		shared_ptr<LogicalSpace> mLSpace;
		shared_ptr<VirtualSpace> mVSpace;
		IGraphics *mGraphics;
	};
}

#endif // FORM_H

