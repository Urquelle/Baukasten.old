#ifndef IFONT_H_1ZHU2XBV
#define IFONT_H_1ZHU2XBV

#include "core/Color"
#include "core/Math"
#include "graphics/Global"

namespace Baukasten {
	class BAUKASTEN_EXPORT IFont {
	public:
		virtual void render( const string&, const vec3<float>&, const Color& ) = 0;

		virtual void setSize( const u32 ) = 0;
		virtual u32 size() const = 0;

		virtual void setFont( const string& ) = 0;
		virtual string font() const = 0;
	};
} /* Baukasten  */

#endif /* end of include guard: IFONT_H_1ZHU2XBV */

