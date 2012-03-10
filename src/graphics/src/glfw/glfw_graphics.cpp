#include "graphics/include/glfw/glfw_graphics.h"

#include "core/CoreServices"
#include "graphics/Font"
#include "graphics/Image"
#include "model/Form"

#include "graphics/include/glfw/glfw_graphics_helper.h"
#include "graphics/include/glfw/node.h"

using namespace Baukasten;

typedef map<string, GLuint> GLCache;

// GlfGraphicsPrivate {{{
class Baukasten::GlfwGraphicsPrivate {
public:
	GlfwGraphicsPrivate( GlfwGraphics *master ) :
		m_font( 0 ),
		m_master( master ),
		m_program( 0 ),
		m_vao( 0 )
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
		result = _initProgram( m_program );

		m_font = new Font( "/usr/share/fonts/corefonts/georgia.ttf" );

		m_master->m_initialised = true;

		return 1;
	}

	void createWindow( const vec2<u32> &size, const wstring &title )
	{
		setWindowSize( size );
		setWindowCaption( title );
	}

	void
	render( Form *form )
	{
		_computeFps( m_t0, m_t1, m_frames, m_fps );

	 	glClear( GL_COLOR_BUFFER_BIT );

		form->constructScene();
		form->render();

		for ( s32 i = 0; i < m_nodes.size(); ++i ) {
			m_nodes[i]->render();
		}

		m_nodes.clear();
		glfwSwapBuffers();
	}

	float
	fps() const
	{
		return m_fps;
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
	drawImage( const string &path, const vec2<float> &size,
			const vec3<float> &pos )
	{
		Image image( path );
		auto t = m_cache.find( path );
		if ( t == m_cache.end() ) {
			image.read();
		}
		drawImage( image, size, pos );
	}

	void
	drawImage( Image &image, const vec2<float> &size, const vec3<float> &pos )
	{
		// transform to normalised [-1.0, 1.0]
		float xMin = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] );
		float xMax = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] + size[BK_WIDTH] );
		float yMin = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] ) * -1;
		float yMax = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] + size[BK_HEIGHT] ) * -1;

		GLfloat vertices[] = {
			// vertex coordinates
			xMin, yMin, pos[BK_Z], 1.0f,
			xMax, yMin, pos[BK_Z], 1.0f,
			xMax, yMax, pos[BK_Z], 1.0f,
			xMin, yMax, pos[BK_Z], 1.0f,

			// texture coordinates
			// ** we have to remap the coordinates here somewhat, as the
			// ** y vertex coordinates are mirrored by the -1.0 multiplication
			0.0f, 1.0f, 0.0f,      1.0f,
			1.0f, 1.0f, 0.0f,      1.0f,
			1.0f, 0.0f, 0.0f,      1.0f,
			0.0f, 0.0f, 0.0f,      1.0f
		};

		GLuint tbo;
		auto t = m_cache.find( image.path() );
		if ( t == m_cache.end() ) {
			image.read();

			glGenTextures( 1, &tbo );
			glBindTexture( GL_TEXTURE_2D, tbo );

			glTexImage2D(
				GL_TEXTURE_2D, 0, GL_RGBA,
				image.width(), image.height(), 0, GL_RGBA,
				GL_UNSIGNED_BYTE, image.data()
			);

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

			glBindTexture( GL_TEXTURE_2D, 0 );

			image.close();

			m_cache[ image.path() ] = tbo;
		} else {
			tbo = t->second;
		}

		QuadNode *node = new QuadNode( GL_QUADS, 4, 4 );

		GLuint vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		node->setProgram( m_program );
		node->setTbo( tbo );
		node->setVbo( vbo );

		m_nodes.push_back( node );
	}

	void
	drawLine( const vec3<float> &from, const vec3<float> &to,
			const Color &c, const float width = 1.0f )
	{
		float r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		float xDiv = m_windowSize[BK_X] / 2, yDiv = m_windowSize[BK_Y] / 2;
		float fromX = ( from[BK_X] - xDiv ) / xDiv;
		float fromY = ( from[BK_Y] - yDiv ) / yDiv;
		float toX = ( to[BK_X] - xDiv ) / xDiv;
		float toY = ( to[BK_Y] - yDiv ) / yDiv;

		GLfloat vertices[] = {
			fromX, fromY, from[BK_Z], 1.0f,
			toX,   toY,   to[BK_Z],   1.0f,
			r, g, b, a,
			r, g, b, a
		};

		LineNode *node = new LineNode( GL_POINTS, 4, 2 );

		GLuint vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		node->setProgram( m_program );
		node->setVbo( vbo );
		node->setWidth( width );

		m_nodes.push_back( node );
	}

	void
	drawPoint( const vec3<float> &pos, const u32 size, const Color &c )
	{
		float r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		float x = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] );
		float y = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] ) * -1;

		GLfloat vertices[] = {
			x, y, pos[BK_Z], 1.0f,
			r, g, b, a
		};

		PointNode *node = new PointNode( GL_POINTS, 4, 1 );

		GLuint vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		node->setProgram( m_program );
		node->setSize( size );
		node->setVbo( vbo );

		m_nodes.push_back( node );
	}

	void
	drawRect( const vec2<float> &size, const vec3<float> &pos, const Color &c )
	{
		float r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		// transform display space coordinates to clip space
		float xMin = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] );
		float xMax = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] + size[BK_WIDTH] );
		float yMin = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] ) * -1;
		float yMax = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] + size[BK_HEIGHT] ) * -1;

		GLfloat vertices[] = {
			xMin, yMin, pos[BK_Z], 1.0f,
			xMax, yMin, pos[BK_Z], 1.0f,
			xMax, yMax, pos[BK_Z], 1.0f,
			xMin, yMax, pos[BK_Z], 1.0f,
			r, g, b, a,
			r, g, b, a,
			r, g, b, a,
			r, g, b, a
		};

		QuadNode *node = new QuadNode( GL_QUADS, 4, 4 );

		GLuint vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		node->setProgram( m_program );
		node->setVbo( vbo );

		m_nodes.push_back( node );
	}

	void
	drawText( const string &text, const vec3<float> &pos, const Color &c )
	{
		TextNode *node = new TextNode( m_font, text, pos, c );
		m_nodes.push_back( node );
	}

	void
	setWindowCaption( const wstring &title )
	{
		m_title = _toString( title );
		glfwSetWindowTitle( m_title.c_str() );
	}

	void
	setWindowSize( const vec2<u32> &size )
	{
		glfwSetWindowSize( (GLsizei) size[BK_X], (GLsizei) size[BK_Y] );
		glViewport( 0, 0, size[BK_X], size[BK_Y] );
		m_windowSize = size;
	}

private:
	GLCache        m_cache;
	Font*          m_font;
	float          m_fps;
	u32            m_frames;
	GlfwGraphics*  m_master;
	vector<Node*>  m_nodes;
	GLuint         m_program;
	float          m_t0;
	float          m_t1;
	string         m_title;
	GLuint         m_vao;
	vec2<u32>      m_windowSize;
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
GlfwGraphics::createWindow( const vec2<u32> &size, const wstring &title )
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
GlfwGraphics::drawImage( Image &image, const vec2<float> &size,
		const vec3<float> &pos )
{
	m_impl->drawImage( image, size, pos );
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
GlfwGraphics::drawText( const string &text, const vec3<float> &pos,
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
GlfwGraphics::setWindowCaption( const wstring &title )
{
	m_impl->setWindowCaption( title );
}

void
GlfwGraphics::setWindowSize( const u32 width, const u32 height )
{
	m_impl->setWindowSize( { width, height } );
}

