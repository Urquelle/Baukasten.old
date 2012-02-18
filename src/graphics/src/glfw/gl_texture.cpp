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
			mSource( path ),
			mMaster( master ),
			mSize( size )
		{
		}

		virtual ~GlTexturePrivate()
		{
		}

		string
		source() const
		{
			return mSource;
		}

	private:
		string       mSource;
		GLuint       mId;
		GlTexture*   mMaster;
		vec2<float>  mSize;
	};
} /* Baukasten */

GlTexture::GlTexture( const string &filePath, const vec2<float> &size ) :
	mImpl( new GlTexturePrivate( this, filePath, size ) )
{
}

GlTexture::~GlTexture()
{
}

string
GlTexture::source() const
{
	return mImpl->source();
}

