#ifndef FONT_H_I5KJO3DB
#define FONT_H_I5KJO3DB

#include "global.h"

namespace Baukasten {
	class FontPrivate;
	class Colour;

	class Font {
	public:
		Font();
		Font( const char* );

		virtual ~Font();

		void setFace( const char* );
		void setSize( const uint );

		void render( const v3<float>&, const char*, const Colour& );

	private:
		friend class FontPrivate;
		FontPrivate*	mImpl;
	};
} /* Baukasten */

#endif /* end of include guard: FONT_H_I5KJO3DB */

