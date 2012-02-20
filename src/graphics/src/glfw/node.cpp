#include "graphics/include/glfw/node.h"

#include "core/Debug"
#include "graphics/include/glfw/gl_texture.h"

#include <GL/glu.h>
#include <GL/glext.h>


using namespace Baukasten;

namespace Baukasten {
	class NodePrivate {
	public:
		NodePrivate(Node *master, GLenum glType, const u32 vertexCount, const u32 indexCount) :
			m_glType( glType ),
			m_indexCount( indexCount ),
			m_master( master ),
			m_vertexCount( vertexCount )
		{
		}

		virtual ~NodePrivate()
		{
		}

		void
		prepare()
		{
			glBindBuffer( GL_ARRAY_BUFFER, m_master->vbo );

			// read first three bytes off of the buffer to get the color
			GLuint colorSize = sizeof( float ) * 3;
			GLfloat *color = static_cast<GLfloat*>(
				glMapBufferRange( GL_ARRAY_BUFFER, 0, colorSize, GL_MAP_READ_BIT )
			);

			if ( color )
				glColor3fv( color );

			glVertexPointer( mVertexCount, GL_FLOAT, 0, BUFFER_OFFSET( colorSize ) );

			if ( mTextures.size() > 0 ) {
				glBindBuffer( GL_ARRAY_BUFFER, mTextures[0]->cbo() );
				glTexCoordPointer( 2, GL_UNSIGNED_BYTE, 0, BUFFER_OFFSET(0) );
				glBindTexture( GL_TEXTURE_2D, mTextures[0]->tbo() );
			}
		}

		void
		render()
		{
			prepare();
			glDrawArrays( m_glType, 0, m_indexCount );
			cleanup();
		}

		void
		addTexture( GlTexture *tex )
		{
			m_textures.push_back( tex );
		}

		void
		cleanup()
		{
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindTexture( GL_TEXTURE_2D, 0 );
			glDeleteBuffers( 1, &m_master->vbo );
		}

	private:
		GLenum          m_glType;
		u32             m_indexCount;
		Node*           m_master;
		s8*             m_offset;
		vector<GlTexture*>  m_textures;
		u32             m_vertexCount;
	};
} /* Baukasten */

// Node
Node::Node( GLenum glType, const u32 vertexCount, const u32 indexCount ) :
	m_impl( new NodePrivate( this, glType, vertexCount, indexCount ) )
{
}

Node::~Node()
{
}

void
Node::prepare()
{
	m_impl->prepare();
}

void
Node::render()
{
	m_impl->render();
}

void
Node::addTexture( GlTexture *tex )
{
	m_impl->addTexture( tex );
}

void
Node::cleanup()
{
	m_impl->cleanup();
}

// LineNode
LineNode::LineNode( GLenum glType, const u32 vertexCount, const u32 indexCount ) :
	Node( glType, vertexCount, indexCount ),
	m_width( 1.0 ), m_stipple( 1 )
{
}

LineNode::~LineNode()
{
}

void
LineNode::setPattern( const u16 pattern )
{
	m_stipple = pattern;
}

u16
LineNode::pattern() const
{
	return m_stipple;
}

void
LineNode::setWidth( const float width )
{
	m_width = width;
}

float
LineNode::width() const
{
	return m_width;
}

void
LineNode::prepare()
{
	glLineWidth( m_width );
	glLineStipple( 1, m_stipple );
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
	m_size = size;
}

u32
PointNode::size() const
{
	return m_size;
}

void
PointNode::prepare()
{
	glPointSize( m_size );
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

