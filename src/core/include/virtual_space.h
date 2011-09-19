#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "global.h"

namespace Baukasten {
	class Drawable;

	class BAUKASTEN_EXPORT VirtualSpace {
	public:
		VirtualSpace();
		virtual ~VirtualSpace();

		Drawable* getEntity( const std::string& ) const;
		void addEntity( Drawable* );
		list<Drawable*> getEntities() const;
		bool hasEntity( const string& ) const;
		void removeEntity( const string& );

	private:
		list<Drawable*>			mList;
		map<string, Drawable*>	mMap;
	};
}

#endif // VIRTUAL_SPACE_H

