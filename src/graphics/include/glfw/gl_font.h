#ifndef GL_FONT_H_YX7ETJ8M
#define GL_FONT_H_YX7ETJ8M

#include "core/Color"
#include "core/Math"
#include "graphics/Global"
#include "graphics/IFont"

namespace Baukasten {
	class GlFontPrivate;

	class GlFont : public IFont {
	public:
		GlFont();
		GlFont( const string& );
		GlFont( const string&, const u32 );

		virtual ~GlFont();

		virtual void render( const string&,
				const vec3<float>&, const Color& );

	private:
		BK_PIMPL_PTR( GlFont );
	};
} /* Baukasten */

#endif /* end of include guard: GL_FONT_H_YX7ETJ8M */

