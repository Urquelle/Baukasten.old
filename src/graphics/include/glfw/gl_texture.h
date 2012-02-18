#ifndef TEXTURE_H_RPDZKCSP
#define TEXTURE_H_RPDZKCSP

#include "core/Math"
#include "graphics/Global"
#include "graphics/ITexture"

#include <GL/glew.h>

namespace Baukasten {
	class GlTexturePrivate;

	class BAUKASTEN_EXPORT GlTexture : public ITexture {
	public:
		GlTexture( const string&, const vec2<float>& );
		virtual ~GlTexture();

		u32     bufferObject() const;
		void    setBufferObject( u32 );
		string  source() const;

		GLuint tbo, cbo;

	private:
		BK_PIMPL_PTR(GlTexture);
	};
} /* Baukasten  */

#endif /* end of include guard: TEXTURE_H_RPDZKCSP */
