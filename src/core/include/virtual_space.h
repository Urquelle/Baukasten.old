#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "global.h"

#include "entity_manager.h"

namespace Baukasten {
	class Drawable;

	class BAUKASTEN_EXPORT VirtualSpace : public EntityManager {
	public:
		VirtualSpace();
		virtual ~VirtualSpace();

		Drawable* getDrawable( const std::string& ) const;

		void addEntity( Drawable* );
		DrawableList getEntities() const;

	private:
		DrawableList mDrawables;
	};
}

#endif // VIRTUAL_SPACE_H

