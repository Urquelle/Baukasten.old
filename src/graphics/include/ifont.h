#ifndef IFONT_H_1ZHU2XBV
#define IFONT_H_1ZHU2XBV

#include "core/Color"
#include "core/Math"
#include "graphics/Global"

namespace Baukasten {
	class IFont {
	public:
		virtual void render( const string&, const vec3<float>&, const Color& ) = 0;
	};
} /* Baukasten  */

#endif /* end of include guard: IFONT_H_1ZHU2XBV */

