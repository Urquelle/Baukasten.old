#ifndef GL_FONT_H_YX7ETJ8M
#define GL_FONT_H_YX7ETJ8M

#include "core/Color"
#include "core/Math"
#include "graphics/Global"
#include "graphics/IFont"

namespace Baukasten {
	class GlFontPrivate;

	class BAUKASTEN_EXPORT GlFont : public IFont {
	public:
		GlFont( const string& );
		GlFont( const string&, const u32 );

		virtual ~GlFont();

		virtual void render( const string&,
				const vec3<float>&, const Color& );

		virtual void setSize( const u32 );
		virtual u32 size() const;

		virtual void setFont( const string& );
		virtual string font() const;

	private:
		BK_PIMPL_PTR( GlFont );
	};
} /* Baukasten */

#endif /* end of include guard: GL_FONT_H_YX7ETJ8M */

