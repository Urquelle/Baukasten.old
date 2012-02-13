#ifndef FONT_H_I5KJO3DB
#define FONT_H_I5KJO3DB

#include "model/Global"
#include "core/Math"

namespace Baukasten {
	class FontPrivate;
	class Color;

	class Font {
	public:
		Font();
		Font( const char* );

		virtual ~Font();

		void setFace( const char* );
		void setSize( const int32 );

		void render( const vec3<float>&, const char*, const Color& );

		// TODO: don't render, return bitmap data instead for the graphics
		// backend.

	private:
		friend class FontPrivate;
		FontPrivate*	mImpl;
	};
} /* Baukasten */

#endif /* end of include guard: FONT_H_I5KJO3DB */

