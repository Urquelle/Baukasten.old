#include "graphics/include/glfw/gl_texture.h"

#include "core/Debug"

#include <GL/gl.h>

using namespace Baukasten;

// GlTexturePrivate
namespace Baukasten {
	class GlTexturePrivate {
	public:
		GlTexturePrivate( GlTexture *master, const string &path,
				const vec2<float> &size ) :
			m_master( master ),
			m_size( size ),
			m_source( path )
		{
		}

		virtual ~GlTexturePrivate()
		{
			glDeleteTextures( 1, &m_tbo );
		}

		string
		source() const
		{
			return m_source;
		}

		void
		setCbo( GLuint cbo )
		{
			m_cbo = cbo;
		}

		GLuint
		cbo() const
		{
			return m_cbo;
		}

		void
		setTbo( GLuint tbo )
		{
			m_tbo = tbo;
		}

		GLuint
		tbo() const
		{
			return m_tbo;
		}

	private:
		GLuint       m_cbo;
		GlTexture*   m_master;
		vec2<float>  m_size;
		string       m_source;
		GLuint       m_tbo;
	};
} /* Baukasten */

GlTexture::GlTexture( const string &filePath, const vec2<float> &size ) :
	m_impl( new GlTexturePrivate( this, filePath, size ) )
{
}

GlTexture::~GlTexture()
{
	delete m_impl;
}

string
GlTexture::source() const
{
	return m_impl->source();
}

void
GlTexture::setCbo( GLuint cbo )
{
	m_impl->setCbo( cbo );
}

GLuint
GlTexture::cbo() const
{
	return m_impl->cbo();
}

void
GlTexture::setTbo( GLuint tbo )
{
	m_impl->setTbo( tbo );
}

GLuint
GlTexture::tbo() const
{
	return m_impl->tbo();
}

