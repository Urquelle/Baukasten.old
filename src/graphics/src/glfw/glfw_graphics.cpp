#include "graphics/GraphicsImpl"

#include "core/CoreServices"
#include "core/Font"
#include "graphics/Image"
#include "model/Form"

#include "graphics/include/glfw/gl_texture.h"
#include "graphics/include/glfw/glfw_graphics_helper.h"
#include "graphics/include/glfw/node.h"

using namespace Baukasten;

// GlfGraphicsPrivate {{{
class Baukasten::GlfwGraphicsPrivate {
public:
	GlfwGraphicsPrivate( GlfwGraphics *master ) :
		m_master( master ),
		m_font( new Font() ),
		m_program( 0 )
	{
	}

	virtual ~GlfwGraphicsPrivate()
	{
	}

	int init( CoreServices *services )
	{
		bool result = false;

		m_t0 = glfwGetTime();

		result = _init();
		result = _initProgram( &m_program );

		m_master->m_initialised = true;

		return 1;
	}

	void createWindow( const vec2<int> &size, const std::wstring &title )
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glfwSetWindowSize( (GLsizei) size[BK_X], (GLsizei) size[BK_Y] );
		glViewport( 0, 0, size[BK_X], size[BK_Y] );
		setWindowCaption( title );
	}

	void
	render( Form *form )
	{
		_computeFps( m_t0, m_t1, m_frames, m_fps );

	 	glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram( m_program );

		form->constructScene();
		form->render();

		for ( s32 i = 0; i < m_nodes.size(); ++i ) {
			m_nodes[i]->render();
		}

		glUseProgram(0);
		m_nodes.clear();

		glfwSwapBuffers();
	}

	float
	fps() const
	{
		return m_fps;
	}

	void
	setWindowCaption( const std::wstring &title )
	{
		glfwSetWindowTitle( _toString( title ).c_str() );
	}

	void
	shutdown()
	{
		for ( s32 i = 0; i < m_textures.size(); ++i )
			delete m_textures.at(i);

		m_textures.clear();
		glfwTerminate();
	}

	void
	drawCircle( const vec3<float> &pos, const u32 radius, const Color &c )
	{
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f( pos[BK_X], pos[BK_Y] );
			for ( float i = 0; i <= 2 * M_PI + 0.1f; i += 0.1f ) {
				glVertex2f(
					pos[BK_X] + sin(i) * radius,
					pos[BK_Y] + cos(i) * radius
				);
			}
		glEnd();
	}

	void
	drawImage( const string &filePath, const vec2<float> &size,
			const vec3<float> &pos )
	{
		float xDiv = 1024 / 2, yDiv = 768 / 2;

		// transform display space coordinates to clip space
		float xMin = ( pos[BK_X] - xDiv ) / xDiv;
		float xMax = ( pos[BK_X] + size[BK_WIDTH] - xDiv ) / xDiv;
		float yMin = ( pos[BK_Y] - yDiv ) / yDiv;
		float yMax = ( pos[BK_Y] + size[BK_HEIGHT] - yDiv ) / yDiv;

		GLfloat vertices[] = {
			xMin, yMin, pos[BK_Z],
			xMax, yMin, pos[BK_Z],
			xMax, yMax, pos[BK_Z],
			xMin, yMax, pos[BK_Z]
		};


		QuadNode *node = new QuadNode( GL_QUADS, 2, 4 );


		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		m_nodes.push_back( node );
	}

	void
	drawLine( const vec3<float> &from, const vec3<float> &to,
			const Color &c, const float width = 1.0f )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			from[BK_X], from[BK_Y],
			to[BK_X], to[BK_Y]
		};

		LineNode *node = new LineNode( GL_POINTS, 2, 2 );

		node->setWidth( width );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		m_nodes.push_back( node );
	}

	void
	drawPoint( const vec3<float> &pos, const u32 size, const Color &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		float xDiv = 1024 / 2, yDiv = 768 / 2;
		float x = ( pos[BK_X] - xDiv ) / xDiv;
		float y = ( pos[BK_Y] - yDiv ) / yDiv * -1;

		GLfloat vertices[] = {
			x, y, pos[BK_Z],
			r, g, b
		};

		PointNode *node = new PointNode( GL_POINTS, 3, 1 );

		node->setSize( size );
		node->setProgram( m_program );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		m_nodes.push_back( node );
	}

	void
	drawRect( const vec2<float> &size, const vec3<float> &pos, const Color &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		float xDiv = 1024 / 2, yDiv = 768 / 2;

		// transform display space coordinates to clip space
		float xMin = ( pos[BK_X] - xDiv ) / xDiv;
		float xMax = ( pos[BK_X] + size[BK_WIDTH] - xDiv ) / xDiv;
		float yMin = ( pos[BK_Y] - yDiv ) / yDiv * -1;
		float yMax = ( pos[BK_Y] + size[BK_HEIGHT] - yDiv ) / yDiv * -1;

		GLfloat vertices[] = {
			xMin, yMin, pos[BK_Z],
			xMax, yMin, pos[BK_Z],
			xMax, yMax, pos[BK_Z],
			xMin, yMax, pos[BK_Z],
			r, g, b,
			r, g, b,
			r, g, b,
			r, g, b,
		};

		QuadNode *node = new QuadNode( GL_QUADS, 3, 4 );

		node->setProgram( m_program );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		m_nodes.push_back( node );
	}

	void
	drawText( const wchar_t *text, const vec3<float> &pos, const Color &c )
	{
		m_font->render(
			pos,
			_toString( wstring(text) ).c_str(),
			c
		);
	}

private:
	GlfwGraphics*		m_master;
	vector<Node*>		m_nodes;
	vector<GlTexture*>	m_textures;
	Font*				m_font;
	GLuint              m_program;

	float				m_t0, m_t1, m_frames, m_fps;
};

// }}}

GlfwGraphics::GlfwGraphics() :
	m_impl( new GlfwGraphicsPrivate( this ) )
{
}

GlfwGraphics::~GlfwGraphics()
{
	delete m_impl;
}

int
GlfwGraphics::init( CoreServices *services )
{
	return m_impl->init( services );
}

void
GlfwGraphics::createWindow( const vec2<int> &size, const std::wstring &title )
{
	m_impl->createWindow( size, title );
}

void
GlfwGraphics::render( Form *form )
{
	m_impl->render( form );
}

void
GlfwGraphics::shutdown()
{
	m_impl->shutdown();
}

void
GlfwGraphics::drawCircle( const vec3<float> &pos, const u32 radius,
		const Color &c )
{
	m_impl->drawCircle( pos, radius, c );
}

void
GlfwGraphics::drawImage( const string &filePath, const vec2<float> &size,
		const vec3<float> &pos )
{
	m_impl->drawImage( filePath, size, pos );
}

void
GlfwGraphics::drawLine( const vec3<float> &from, const vec3<float> &to,
		const Color &color, const float width )
{
	m_impl->drawLine( from, to, color, width );
}

void
GlfwGraphics::drawPoint( const vec3<float> &pos,
		const u32 size, const Color &color )
{
	m_impl->drawPoint( pos, size, color );
}

void
GlfwGraphics::drawRect( const vec2<float> &size,
		const vec3<float> &pos, const Color &color )
{
	m_impl->drawRect( size, pos, color );
}

void
GlfwGraphics::drawText( const wchar_t *text, const vec3<float> &pos,
		const Color &color )
{
	m_impl->drawText( text, pos, color );
}

float
GlfwGraphics::fps() const
{
	return m_impl->fps();
}

void
GlfwGraphics::setWindowCaption( const std::wstring &title )
{
	m_impl->setWindowCaption( title );
}

