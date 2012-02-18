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
			mMaster( master ),
			mSize( size ),
			mSource( path )
		{
		}

		virtual ~GlTexturePrivate()
		{
			glDeleteTextures( 1, &mTbo );
		}

		string
		source() const
		{
			return mSource;
		}

		void
		setCbo( GLuint cbo )
		{
			mCbo = cbo;
		}

		GLuint
		cbo() const
		{
			return mCbo;
		}

		void
		setTbo( GLuint tbo )
		{
			mTbo = tbo;
		}

		GLuint
		tbo() const
		{
			return mTbo;
		}

	private:
		GLuint       mCbo;
		GlTexture*   mMaster;
		vec2<float>  mSize;
		string       mSource;
		GLuint       mTbo;
	};
} /* Baukasten */

GlTexture::GlTexture( const string &filePath, const vec2<float> &size ) :
	mImpl( new GlTexturePrivate( this, filePath, size ) )
{
}

GlTexture::~GlTexture()
{
	delete mImpl;
}

string
GlTexture::source() const
{
	return mImpl->source();
}

void
GlTexture::setCbo( GLuint cbo )
{
	mImpl->setCbo( cbo );
}

GLuint
GlTexture::cbo() const
{
	return mImpl->cbo();
}

void
GlTexture::setTbo( GLuint tbo )
{
	mImpl->setTbo( tbo );
}

GLuint
GlTexture::tbo() const
{
	return mImpl->tbo();
}

