#include "graphics/include/glfw/node.h"

#include "model/Debug"
#include "graphics/ITexture"

#include <GL/glu.h>
#include <GL/glext.h>


using namespace Baukasten;

namespace Baukasten {
	class NodePrivate {
	public:
		NodePrivate(Node *master, GLenum glType, const u32 vertexCount, const u32 indexCount) :
			mGlType( glType ),
			mIndexCount( indexCount ),
			mMaster( master ),
			mVertexCount( vertexCount )
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
			GLfloat *color = static_cast<GLfloat*>(
				glMapBufferRange( GL_ARRAY_BUFFER, 0, colorSize, GL_MAP_READ_BIT )
			);

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
		GLenum          mGlType;
		u32             mIndexCount;
		Node*           mMaster;
		s8*             mOffset;
		u32             mVertexCount;
	};
} /* Baukasten */

// Node
Node::Node( GLenum glType, const u32 vertexCount, const u32 indexCount ) :
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
Node::addTexture( GlTexture *tex )
{
	mImpl->addTexture( tex );
}

void
Node::cleanup()
{
	mImpl->cleanup();
}

// LineNode
LineNode::LineNode( GLenum glType, const u32 vertexCount, const u32 indexCount ) :
	Node( glType, vertexCount, indexCount ),
	mWidth( 1.0 ), mStipple( 1 )
{
}

LineNode::~LineNode()
{
}

void
LineNode::setPattern( const u16 pattern )
{
	mStipple = pattern;
}

u16
LineNode::pattern() const
{
	return mStipple;
}

void
LineNode::setWidth( const float width )
{
	mWidth = width;
}

float
LineNode::width() const
{
	return mWidth;
}

void
LineNode::prepare()
{
	glLineWidth( mWidth );
	glLineStipple( 1, mStipple );
	glEnable( GL_LINE_STIPPLE );
}

void
LineNode::cleanup()
{
	glDisable( GL_LINE_STIPPLE );
}

// PointNode
PointNode::PointNode( GLenum glType, const u32 vertexCount, const u32 indexCount ) :
	Node( glType, vertexCount, indexCount )
{
}

PointNode::~PointNode()
{
}

void
PointNode::setSize( const u32 size )
{
	mSize = size;
}

u32
PointNode::size() const
{
	return mSize;
}

void
PointNode::prepare()
{
	glPointSize( mSize );
}

// QuadNode
QuadNode::QuadNode( GLenum glType, const u32 vertexCount, const u32 indexCount ) :
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

