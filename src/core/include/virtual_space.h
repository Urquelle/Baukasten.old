#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "global.h"
#include "abstract_space.h"

namespace Baukasten {
	class Drawable;

	class BAUKASTEN_EXPORT VirtualSpace : public AbstractSpace {
	public:
		VirtualSpace( const std::string& );
		virtual ~VirtualSpace();

		void append( const Drawable* );
	};
}

#endif // VIRTUAL_SPACE_H

