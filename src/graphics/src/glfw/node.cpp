#include "graphics/include/glfw/node.h"

#include "model/Debug"
#include "graphics/ITexture"

#include <GL/glu.h>
#include <GL/glext.h>


#define BUFFER_OFFSET(offset) ((char*) NULL + offset)

using namespace Baukasten;

namespace Baukasten {
	class NodePrivate {
	public:
		NodePrivate(Node *master, GLenum glType, int vertexCount, int indexCount) :
			mMaster( master ), mGlType( glType ), mVertexCount( vertexCount ),
			mIndexCount( indexCount )
		{
		}

		virtual ~NodePrivate()
		{
		}

		void
		prepare()
		{
			glBindBuffer( GL_ARRAY_BUFFER, mMaster->vbo );

			// read first three bytes off of the buffer to get the color
			GLuint colorSize = sizeof( float ) * 3;
			GLfloat *color = static_cast<GLfloat*>( glMapBufferRange( GL_ARRAY_BUFFER, 0, colorSize, GL_MAP_READ_BIT ) );

			if ( color )
				glColor3fv( color );

			mOffset = BUFFER_OFFSET( colorSize );
			glVertexPointer( mVertexCount, GL_FLOAT, 0, mOffset );
		}

		virtual void
		render()
		{
			prepare();
			glDrawArrays( mGlType, 0, mIndexCount );
			cleanup();
		}

		void
		cleanup()
		{
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glDeleteBuffers( 1, &mMaster->vbo );
		}

	private:
		Node*	mMaster;
		GLenum	mGlType;

		int		mVertexCount;
		int		mIndexCount;
		char*	mOffset;
	};
} /* Baukasten */

Node::Node( GLenum glType, int vertexCount, int indexCount ) :
	mImpl( new NodePrivate( this, glType, vertexCount, indexCount ) )
{
}

Node::~Node()
{
}

void
Node::prepare()
{
	mImpl->prepare();
}

void
Node::render()
{
	mImpl->render();
}

void
Node::cleanup()
{
	mImpl->cleanup();
}

// LineNode
LineNode::LineNode( GLenum glType, int vertexCount, int indexCount ) :
	Node( glType, vertexCount, indexCount )
{
}

LineNode::~LineNode()
{
}

void
LineNode::prepare()
{
	// do some preparations 'n shit
}

// PointNode
PointNode::PointNode( GLenum glType, int vertexCount, int indexCount ) :
	Node( glType, vertexCount, indexCount )
{
}

PointNode::~PointNode()
{
}

void
PointNode::prepare()
{
	// do some preparations 'n shit
}

// QuadNode
QuadNode::QuadNode( GLenum glType, int vertexCount, int indexCount ) :
	Node( glType, vertexCount, indexCount )
{
}

QuadNode::~QuadNode()
{
}

void
QuadNode::prepare()
{
	// do some preparations 'n shit
}

// TextureNode
TextureNode::TextureNode( ITexture *tex) :
	Node( 0, 0, 0 ),
	mTexture( tex )
{
}

TextureNode::~TextureNode()
{
}

void
TextureNode::prepare()
{
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER, vbo );
}

void
TextureNode::cleanup()
{
	glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
}

void
TextureNode::render()
{
	prepare();

	glRasterPos2i( mPosition[BK_X], mSize[BK_HEIGHT] );
	glDrawPixels(
		mSize[BK_WIDTH], mSize[BK_HEIGHT],
		GL_RGB, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0)
	);

	cleanup();
}

void
TextureNode::setSize( const vec2<float> &size )
{
	mSize = size;
}

void
TextureNode::setPosition( const vec3<float> &pos )
{
	mPosition = pos;
}

