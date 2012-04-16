#include "graphics/include/glfw/node.h"

#include "core/Debug"
#include "graphics/Font"
#include "graphics/include/glfw/gl_texture.h"

#include <GL/glu.h>
#include <GL/glext.h>

using namespace Baukasten;

namespace Baukasten {
	class NodePrivate {
	public:
		NodePrivate(GLenum type,
				const u32 dataPerVertex, const u32 indexCount) :
			m_dataPerVertex( dataPerVertex ),
			m_indexCount( indexCount ),
			m_tbo( 0 ), m_type( type ), m_vbo( 0 )
		{
		}

		virtual ~NodePrivate()
		{
		}

		void
		prepare()
		{
			glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
			glUseProgram( m_program );

			GLuint position = glGetAttribLocation( m_program, "position" );
			GLuint color    = glGetAttribLocation( m_program, "color" );

			glEnableVertexAttribArray(position);
			glEnableVertexAttribArray(color);

			glVertexAttribPointer(
				position, m_dataPerVertex,
				GL_FLOAT, GL_FALSE,
				0, BUFFER_OFFSET( 0 )
			);

			glVertexAttribPointer(
				color, 4,
				GL_FLOAT, GL_FALSE,
				0, BUFFER_OFFSET( m_dataPerVertex * m_indexCount * sizeof(f32) )
			);

			if ( m_tbo ) {
				//glEnable( GL_TEXTURE_2D );
				//glBindBuffer( GL_ARRAY_BUFFER, m_textures[0]->cbo() );
				//glTexCoordPointer( 2, GL_UNSIGNED_BYTE, 0, BUFFER_OFFSET(0) );
				//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
				//glBindTexture( GL_TEXTURE_2D, m_textures[0]->tbo() );
			}
		}

		void
		render()
		{
			prepare();
			glDrawArrays( m_type, 0, m_indexCount );
			cleanup();
		}

		void
		setProgram( GLuint program )
		{
			m_program = program;
		}

		void
		setTbo( const GLuint tbo )
		{
			m_tbo = tbo;
		}

		void
		setVbo( const GLuint vbo )
		{
			m_vbo = vbo;
		}

		void
		cleanup()
		{
			glUseProgram( 0 );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glBindTexture( GL_TEXTURE_2D, 0 );
			glDeleteBuffers( 1, &m_vbo );
			glDisable( GL_TEXTURE_2D );

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}

		GLuint
		tbo() const
		{
			return m_tbo;
		}

		GLuint
		vbo() const
		{
			return m_vbo;
		}

		u32
		dataPerVertex() const
		{
			return m_dataPerVertex;
		}

		u32
		indexCount() const
		{
			return m_indexCount;
		}

		GLenum
		type() const
		{
			return m_type;
		}

		void
		setType( GLenum type )
		{
			m_type = type;
		}

	private:
		u32     m_dataPerVertex;
		u32     m_indexCount;
		s8*     m_offset;
		GLuint  m_program;
		GLuint  m_tbo;
		GLenum  m_type;
		GLuint  m_vbo;
	};
} /* Baukasten */

// Node
Node::Node( GLenum type, const u32 dataPerVertex, const u32 indexCount ) :
	m_impl( new NodePrivate( type, dataPerVertex, indexCount ) )
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
Node::setProgram( GLuint program )
{
	m_impl->setProgram( program );
}

void
Node::setTbo( const GLuint tbo )
{
	m_impl->setTbo( tbo );
}

void
Node::setVbo( GLuint vbo )
{
	m_impl->setVbo( vbo );
}

GLuint
Node::tbo() const
{
	return m_impl->tbo();
}

GLuint
Node::vbo() const
{
	return m_impl->vbo();
}

void
Node::cleanup()
{
	m_impl->cleanup();
}

u32
Node::dataPerVertex() const
{
	return m_impl->dataPerVertex();
}

u32
Node::indexCount() const
{
	return m_impl->indexCount();
}

GLenum
Node::type() const
{
	return m_impl->type();
}

void
Node::setType( GLenum type )
{
	m_impl->setType( type );
}

// LineNode
LineNode::LineNode( GLenum type, const u32 dataPerVertex, const u32 indexCount ) :
	Node( type, dataPerVertex, indexCount ),
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
LineNode::setWidth( const f32 width )
{
	m_width = width;
}

f32
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

// TODO: implement render method in order for prepare to take effect.

// PointNode
PointNode::PointNode( GLenum type, const u32 dataPerVertex, const u32 indexCount ) :
	Node( type, dataPerVertex, indexCount )
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

// TODO: implement render method in order for prepare to take effect.

// QuadNode
QuadNode::QuadNode( GLenum type, const u32 dataPerVertex, const u32 indexCount ) :
	Node( type, dataPerVertex, indexCount )
{
}

QuadNode::~QuadNode()
{
}

void
QuadNode::prepare()
{
	glEnable( GL_TEXTURE_2D );

	glBindBuffer( GL_ARRAY_BUFFER, vbo() );
	glBindTexture( GL_TEXTURE_2D, tbo() );

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glVertexPointer( dataPerVertex(), GL_FLOAT, 0, BUFFER_OFFSET( 0 ) );
	glTexCoordPointer( 4, GL_FLOAT, 0, BUFFER_OFFSET( dataPerVertex() * indexCount() * 4 ) );
}

void
QuadNode::cleanup()
{
	glDisable( GL_TEXTURE_2D );

	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

void
QuadNode::render()
{
	if ( tbo() ) {
		prepare();
		glDrawArrays( type(), 0, indexCount() );
		cleanup();
	} else {
		Node::render();
	}
}

void
QuadNode::setOutline( bool outline )
{
	if ( outline )
		setType( GL_LINE_LOOP );
	else
		setType( GL_QUADS );
}

bool
QuadNode::outline() const
{
	return ( type() == GL_LINE_LOOP );
}

// PolyNode
PolyNode::PolyNode( GLenum type, const u32 dataPerVertex, const u32 indexCount ) :
	Node( type, dataPerVertex, indexCount )
{
}

PolyNode::~PolyNode()
{
}

void
PolyNode::render()
{
	Node::render();
}

void
PolyNode::setOutline( bool outline )
{
	if ( outline )
		setType( GL_LINE_LOOP );
	else
		setType( GL_POLYGON );
}

bool
PolyNode::outline() const
{
	return ( type() == GL_LINE_LOOP );
}

// TextNodePrivate
class Baukasten::TextNodePrivate {
public:
	TextNodePrivate( IFont *font, const string &text, const Vector3 &pos,
			const Color &c ) :
		m_font( font ),
		m_text( text ),
		m_pos( pos ),
		m_color( c )
	{
	}

	~TextNodePrivate()
	{
	}

	void
	render()
	{
		m_font->render( m_text, m_pos, m_color );
	}

private:
	IFont*    m_font;
	string    m_text;
	Vector3   m_pos;
	Color     m_color;
};

// TextNode
TextNode::TextNode( IFont *font, const string &text,
		const Vector3 &pos, const Color &c ) :
	Node( 0, 0, 0 ),
	m_impl( new TextNodePrivate( font, text, pos, c ) )
{
}

TextNode::~TextNode()
{
	delete m_impl;
}

void
TextNode::render()
{
	m_impl->render();
}

