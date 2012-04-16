#ifndef TEXTURE_H_RPDZKCSP
#define TEXTURE_H_RPDZKCSP

#include "graphics/Global"
#include "graphics/ITexture"
#include "math/Vector2"

#include <GL/glew.h>

namespace Baukasten {
	class GlTexturePrivate;

	class BAUKASTEN_EXPORT GlTexture : public ITexture {
	public:
		GlTexture( const string&, const Vector2& );
		virtual ~GlTexture();

		string  source() const;

		void setCbo( GLuint );
		GLuint cbo() const;

		void setTbo( GLuint );
		GLuint tbo() const;

	private:
		BK_IMPL_PTR( GlTexture );
	};
} /* Baukasten  */

#endif /* end of include guard: TEXTURE_H_RPDZKCSP */

