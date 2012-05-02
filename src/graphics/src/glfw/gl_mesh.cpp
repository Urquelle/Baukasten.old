#include "graphics/include/glfw/gl_mesh.h"

#include "core/Assert"

#include <GL/glew.h>
#include <GL/gl.h>

#include <map>

namespace Baukasten {

union _attribute_value {
	f32 value_f32;
	u32 value_u32;
};

typedef map<IMesh::Attribute, _attribute_value> AttributeMap;

class GlMeshPrivate {
public:
	GlMeshPrivate( const f32 *data, const u32 count )
	{
		glGenBuffers( 1, &m_vbo );
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
		glBufferData( GL_ARRAY_BUFFER, count, data, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
	}

	~GlMeshPrivate()
	{
		glDeleteBuffers( 1, &m_vbo );
	}

	void
	cleanup()
	{
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
	}

	u32
	indexCount() const
	{
		return 0;
	}

	bool
	isWireframe() const
	{
		return m_wireframe;
	}

	void
	prepare()
	{
		// PATTERN
		auto it_p = m_attributes.find( IMesh::PATTERN );
		if ( it_p != m_attributes.end() ) {
			glLineStipple( 1, it_p->second.value_f32 );
			glEnable( GL_LINE_STIPPLE );
		}

		// SIZE
		auto it_s = m_attributes.find( IMesh::SIZE );
		if ( it_s != m_attributes.end() )
			glPointSize( it_s->second.value_u32 );

		// WIDTH
		auto it_w = m_attributes.find( IMesh::WIDTH );
		if ( it_w != m_attributes.end() )
			glLineWidth( it_w->second.value_f32 );

		glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	}

	void
	render()
	{
		glDrawArrays( _type(), 0, indexCount() );
	}

	void
	set( IMesh::Attribute attribute, const u32 value )
	{
		m_attributes[ attribute ].value_u32 = value;
	}

	void
	set( IMesh::Attribute attribute, const f32 value )
	{
		m_attributes[ attribute ].value_f32 = value;
	}

	void setType( IMesh::Type type )
	{
		m_type = type;
	}

	void setData( const GLfloat *vertices, const u32 count,
			const u32 offset = 0 )
	{
		vector<Vector3> t_vertices;
		for ( u32 i = 0; i < count; ++i ) {
			if ( i >= offset && (s32)i < count ) {
				t_vertices.push_back( vertices[ i ] );
			} else {
				t_vertices.push_back( m_vertices[ i ] );
			}
		}

		m_vertices = t_vertices;
	}

	void setWireframe( bool wireframe )
	{
		m_wireframe = wireframe;
	}

	IMesh::Type
	type() const
	{
		return m_type;
	}

	GLint
	_type() const
	{
		if ( m_wireframe )
			return GL_LINE_LOOP;

		switch ( m_type ) {
		case IMesh::POINT:
			return GL_POINT;
		case IMesh::LINE:
			return GL_LINE;
		case IMesh::POLYGON:
			return GL_POLYGON;
		case IMesh::QUAD:
			return GL_QUADS;
		case IMesh::TRIANGLE:
			return GL_TRIANGLES;
		default:
			return GL_LINE;
		}
	}

	u32
	vertexCount() const
	{
		return m_vertices.size();
	}

private:
	AttributeMap    m_attributes;
	IMesh::Type     m_type;
	GLuint          m_vbo;
	vector<Vector3> m_vertices;
	bool            m_wireframe;
};

GlMesh::GlMesh() :
	m_impl( NULL )
{
}

GlMesh::~GlMesh()
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	delete m_impl;
}

void
GlMesh::cleanup()
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	m_impl->cleanup();
}

GlMesh&
GlMesh::createMesh( const Type type, const f32 *data, const u32 count )
{
	GlMesh *mesh = new GlMesh();

	mesh->m_impl = new GlMeshPrivate( data, count );
	mesh->m_impl->setType( type );

	return *mesh;
}

GlMesh&
GlMesh::createLine( const Vector3 &from, const Vector3 &to,
		const f32 width )
{
	GLfloat vertices[] = {
		from.x, from.y, from.z, 1.0f,
		to.x,   to.y,   to.z,   1.0f
	};

	GlMesh &mesh = GlMesh::createMesh( LINE, &vertices[0], 8 );
	mesh.m_impl->set( WIDTH, width );
	mesh.m_impl->setData( vertices, 16 );
	return mesh;
}

GlMesh&
GlMesh::createPoint( const Vector3 &pos, const u32 size )
{
	GLfloat vertices[] = { pos.x, pos.y, pos.z, 1.0f };
	GlMesh &mesh = GlMesh::createMesh( POINT, &vertices[0], 4 );
	return mesh;
}

GlMesh&
GlMesh::createRect( const Vector3 &pos, const Vector2 &size )
{
	f32 xMin = pos.x; f32 xMax = pos.x + size.x;
	f32 yMin = pos.y; f32 yMax = pos.y + size.y;

	GLfloat vertices[] = {
		xMin, yMin, pos.z, 1.0f,
		xMax, yMin, pos.z, 1.0f,
		xMax, yMax, pos.z, 1.0f,
		xMin, yMax, pos.z, 1.0f
	};

	GlMesh &mesh = GlMesh::createMesh( QUAD, &vertices[0], 16 );
	return mesh;
}

GlMesh&
GlMesh::createPolygon( const f32 *data, const u32 count )
{
	GlMesh &mesh = GlMesh::createMesh( POLYGON, data, count );
	return mesh;
}

u32
GlMesh::indexCount() const
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	return m_impl->indexCount();
}

bool
GlMesh::isWireframe() const
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	return m_impl->isWireframe();
}

void
GlMesh::set( Attribute attribute, const u32 value )
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	m_impl->set( attribute, value );
}

void
GlMesh::set( Attribute attribute, const f32 value )
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	m_impl->set( attribute, value );
}

void
GlMesh::setData( const f32 *data, const u32 count, const u32 offset )
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	m_impl->setData( data, count, offset );
}

void
GlMesh::setWireframe( bool wireframe )
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	m_impl->setWireframe( wireframe );
}

GlMesh::Type
GlMesh::type() const
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	return m_impl->type();
}

u32
GlMesh::vertexCount() const
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	return m_impl->vertexCount();
}

void
GlMesh::render()
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	prepare();
	m_impl->render();
	cleanup();
}

void
GlMesh::prepare()
{
	BK_ASSERT( m_impl, "implementation pointer not set." );
	m_impl->prepare();
}

} /* Baukasten */

