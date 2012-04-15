#include "graphics/include/glfw/glfw_graphics.h"

#include "core/Version"
#include "graphics/Font"
#include "graphics/Image"
#include "input/IInput"
#include "model/Form"
#include "model/ModelInterface"
#include "services/Services"

#include "graphics/include/glfw/glfw_graphics_helper.h"
#include "graphics/include/glfw/node.h"

#include <sstream>

using namespace Baukasten;

typedef map<string, GLuint> GLCache;

// GlfGraphicsPrivate {{{
class Baukasten::GlfwGraphicsPrivate {
public:
	GlfwGraphicsPrivate( GlfwGraphics *master ) :
		m_master( master ),
		m_program( 0 ),
		m_vao( 0 )
	{
	}

	virtual ~GlfwGraphicsPrivate()
	{
		glfwTerminate();
	}

	void
	init( Services &services )
	{
		m_t0 = glfwGetTime();
		m_master->setIsReady( true );
	}

	void createWindow( const vec2<u32> &size, const string &title,
			IGraphics::WindowFlags flags )
	{
		glfwInit();

		u32 mode = 0;
		if ( flags & IGraphics::WINDOW ) mode = GLFW_WINDOW;
		else if ( flags & IGraphics::FULLSCREEN ) mode = GLFW_FULLSCREEN;

		glfwOpenWindow( size[BK_WIDTH], size[BK_HEIGHT], 0, 0, 0, 0, 0, 0, mode );
		glfwSetWindowSizeCallback( _resize );
		glViewport( 0, 0, size[BK_WIDTH], size[BK_HEIGHT] );
		glewInit();

		_initProgram( m_program );

		setWindowSize( size );
		setWindowTitle( title );

		// notify input service
		Services::instance().inputService().init(
			Services::instance()
		);
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

	f32
	fps() const
	{
		return m_fps;
	}

	void
	shutdown()
	{
		glfwTerminate();
	}

	void
	drawInfo( IFont *font, const vec3<f32> &pos, bool compact,
			IGraphics::InfoFlags flags = IGraphics::DRAW_ALL )
	{
		f32 x = pos[BK_X], y = pos[BK_Y];
		vec2<f32> size({ 200, 150 });

		if ( compact )
			size = { 600, 20 };

		// draw semitransparent rect
		drawRect( size, { x, y, 0.0 }, Color::BK_WHITE );
		x += 10;

		// draw fps
		if ( flags & IGraphics::DRAW_FPS ) {
			stringstream _fps;
			_fps << "fps: " << fps();
			drawText( font, _fps.str(), { x, y + 15, 0 }, Color::BK_BLACK );
		}

		// draw version
		if ( flags & IGraphics::DRAW_VERSION ) {
			stringstream _version;
			_version << "version: " << version();
			if ( compact ) {
				x += 100;
			} else {
				y += 20;
			}

			drawText( font, _version.str(), { x, y + 15, 0 }, Color::BK_BLACK );
		}

		// draw version name
		if ( flags & IGraphics::DRAW_VERSION_NAME ) {
			if ( compact ) {
				x += 100;
			} else {
				y += 20;
			}
			drawText( font, "version name: " + name(), { x, y + 15, 0 }, Color::BK_BLACK );
		}

		// draw time
		if ( flags & IGraphics::DRAW_TIME ) {
			stringstream _time;
			_time << "time: " << time();
			if ( compact ) {
				x += 150;
			} else {
				y += 20;
			}

			drawText( font, _time.str(), { x, y + 15, 0 }, Color::BK_BLACK );
		}

		// draw model information
		if ( flags & IGraphics::DRAW_ENTITY_COUNT ) {
			if ( compact ) {
				x += 100;
			} else {
				y += 20;
			}

			stringstream entityCount;
			entityCount << "entity count: " << ModelInterface::instance().entityCount();
			drawText( font, entityCount.str(), { x, y + 15, 0 }, Color::BK_BLACK );
		}
	}

	void
	drawCircle( const vec3<f32> &pos, const u32 radius, const Color &c )
	{
		glBegin( GL_TRIANGLE_FAN );
			glVertex2f( pos[BK_X], pos[BK_Y] );
			for ( f32 i = 0; i <= 2 * M_PI + 0.1f; i += 0.1f ) {
				glVertex2f(
					pos[BK_X] + sin( i ) * radius,
					pos[BK_Y] + cos( i ) * radius
				);
			}
		glEnd();
	}

	void
	drawImage( const string &path, const vec2<f32> &size,
			const vec3<f32> &pos )
	{
		Image image( path );
		auto t = m_cache.find( path );
		if ( t == m_cache.end() ) {
			image.read();
		}
		drawImage( image, size, pos );
	}

	void
	drawImage( Image &image, const vec2<f32> &size, const vec3<f32> &pos )
	{
		// transform to normalised [-1.0, 1.0]
		f32 xMin = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] );
		f32 xMax = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] + size[BK_WIDTH] );
		f32 yMin = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] ) * -1;
		f32 yMax = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] + size[BK_HEIGHT] ) * -1;

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
	drawLine( const vec3<f32> &from, const vec3<f32> &to,
			const Color &c, const f32 width = 1.0f )
	{
		f32 r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		f32 xDiv = m_windowSize[BK_X] / 2, yDiv = m_windowSize[BK_Y] / 2;
		f32 fromX = ( from[BK_X] - xDiv ) / xDiv;
		f32 fromY = ( from[BK_Y] - yDiv ) / yDiv * -1;
		f32 toX = ( to[BK_X] - xDiv ) / xDiv;
		f32 toY = ( to[BK_Y] - yDiv ) / yDiv * -1;

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
	drawPoint( const vec3<f32> &pos, const u32 size, const Color &c )
	{
		f32 r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		f32 x = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] );
		f32 y = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] ) * -1;

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
	drawRect( const vec2<f32> &size, const vec3<f32> &pos,
			const Color &c, bool outline = false )
	{
		f32 r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		// transform display space coordinates to clip space
		f32 xMin = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] );
		f32 xMax = _normalise( m_windowSize[BK_WIDTH], pos[BK_X] + size[BK_WIDTH] );
		f32 yMin = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] ) * -1;
		f32 yMax = _normalise( m_windowSize[BK_HEIGHT], pos[BK_Y] + size[BK_HEIGHT] ) * -1;

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
		node->setOutline( outline );

		m_nodes.push_back( node );
	}

	void
	drawText( IFont *font, const string &text, const vec3<f32> &pos, const Color &c )
	{
		TextNode *node = new TextNode( font, text, pos, c );
		m_nodes.push_back( node );
	}

	void
	drawPolygon( const vector<vec3<f32>> &vertices,
			const Color &c, bool outline = true )
	{
		f32 r, g, b, a;
		c.rgbF( &r, &g, &b, &a );

		vector<f32> normVertices;

		// push vertices
		for (s32 i = 0; i < vertices.size(); ++i) {
			normVertices.push_back( _normalise( m_windowSize[BK_WIDTH], vertices[i][BK_X] ) );
			normVertices.push_back( _normalise( m_windowSize[BK_HEIGHT], vertices[i][BK_Y] ) * -1.0 );
			normVertices.push_back( 0.0 ); // z
			normVertices.push_back( 1.0 ); // w
		}

		// push color
		for (s32 i = 0; i < vertices.size(); ++i ) {
			normVertices.push_back( r );
			normVertices.push_back( g );
			normVertices.push_back( b );
			normVertices.push_back( a );
		}

		PolyNode *node = new PolyNode( GL_POLYGON, 4, vertices.size() );

		GLuint vbo;
		glGenBuffers( 1, &vbo );
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, normVertices.size() * 4, &normVertices[0], GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		node->setProgram( m_program );
		node->setVbo( vbo );
		node->setOutline( outline );

		m_nodes.push_back( node );
	}

	void
	setWindowTitle( const string &title )
	{
		glfwSetWindowTitle( title.c_str() );
	}

	void
	setWindowSize( const vec2<u32> &size )
	{
		glfwSetWindowSize( (GLsizei) size[BK_X], (GLsizei) size[BK_Y] );
		glViewport( 0, 0, size[BK_X], size[BK_Y] );
		m_windowSize = size;
	}

	f32
	time() const
	{
		return glfwGetTime();
	}

private:
	GLCache        m_cache;
	f32            m_fps;
	u32            m_frames;
	GlfwGraphics*  m_master;
	vector<Node*>  m_nodes;
	GLuint         m_program;
	f32            m_t0;
	f32            m_t1;
	string         m_title;
	GLuint         m_vao;
	vec2<u32>      m_windowSize;
};
// }}}

GlfwGraphics::GlfwGraphics() :
	IGraphics( "GLFW" ),
	m_impl( new GlfwGraphicsPrivate( this ) )
{
}

GlfwGraphics::~GlfwGraphics()
{
	delete m_impl;
}

void
GlfwGraphics::init( Services &services )
{
	m_impl->init( services );
}

void
GlfwGraphics::createWindow( const vec2<u32> &size,
		const string &title, WindowFlags flags )
{
	m_impl->createWindow( size, title, flags );
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
GlfwGraphics::drawInfo( IFont *font, const vec3<f32> &pos,
		bool compact, InfoFlags flags )
{
	m_impl->drawInfo( font, pos, compact, flags );
}

void
GlfwGraphics::drawCircle( const vec3<f32> &pos, const u32 radius,
		const Color &c )
{
	m_impl->drawCircle( pos, radius, c );
}

void
GlfwGraphics::drawImage( const string &path, const vec2<f32> &size,
		const vec3<f32> &pos )
{
	m_impl->drawImage( path, size, pos );
}

void
GlfwGraphics::drawImage( Image &image, const vec2<f32> &size,
		const vec3<f32> &pos )
{
	m_impl->drawImage( image, size, pos );
}

void
GlfwGraphics::drawLine( const vec3<f32> &from, const vec3<f32> &to,
		const Color &color, const f32 width )
{
	m_impl->drawLine( from, to, color, width );
}

void
GlfwGraphics::drawPoint( const vec3<f32> &pos,
		const u32 size, const Color &color )
{
	m_impl->drawPoint( pos, size, color );
}

void
GlfwGraphics::drawPolygon( const vector<vec3<f32>> &vertices,
		const Color &c, bool outline )
{
	m_impl->drawPolygon( vertices, c, outline );
}

void
GlfwGraphics::drawRect( const vec2<f32> &size,
		const vec3<f32> &pos, const Color &color, bool outline )
{
	m_impl->drawRect( size, pos, color, outline );
}

void
GlfwGraphics::drawText( IFont *font, const string &text, const vec3<f32> &pos,
		const Color &color )
{
	m_impl->drawText( font, text, pos, color );
}

f32
GlfwGraphics::fps() const
{
	return m_impl->fps();
}

void
GlfwGraphics::setWindowTitle( const string &title )
{
	m_impl->setWindowTitle( title );
}

void
GlfwGraphics::setWindowSize( const u32 width, const u32 height )
{
	m_impl->setWindowSize( { width, height } );
}

f32
GlfwGraphics::time() const
{
	return m_impl->time();
}

