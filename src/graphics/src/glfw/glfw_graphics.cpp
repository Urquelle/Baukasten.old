#include "graphics/GraphicsImpl"

#include "core/CoreServices"
#include "core/Form"
#include "graphics/Font"
#include "util/Util"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glfw.h>

#include <cmath>
#include <cstring>
#include <vector>

#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)

string toString( const wstring &s )
{
	string str( s.begin(), s.end() );
	str.assign( s.begin(), s.end() );
	return str;
}

void checkForError()
{
	GLuint errCode = glGetError();
	if ( errCode != GL_NO_ERROR ) {
		BK_DEBUG( gluErrorString( errCode ) );
	}
}

void computeFps( float &t0, float &t1, float &frames, float &fps )
{
	t1 = glfwGetTime();

	if ( ( t1 - t0 ) >= 1.0 || frames == 0 ) {
		fps = frames / ( t1 - t0 );
		t0 = t1;
		frames = 0;
	}

	frames++;
}

using namespace Baukasten;

// GlfGraphicsP {{{

struct GraphicsNode {
	GLuint vbo;
	GLenum type;
	int vertexCount;
	int indexCount;
};

class Baukasten::GlfwGraphicsP {
public:
	GlfwGraphicsP( GlfwGraphics *master ) :
		mMaster( master ),
		mFont( new Font() )
	{
	}

	virtual ~GlfwGraphicsP()
	{
	}

	int init( CoreServices *services )
	{
		mT0 = glfwGetTime();

		if ( !glfwInit() ) {
			return 0;
		}

		glfwOpenWindow( 640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
		glViewport( 0, 0, 640.0, 480.0 );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0.0, 640.0, 480.0, 0.0 );
		glewInit();

		mMaster->mInitialised = true;

		return 1;
	}

	void createWindow( const vec2<int> &size, const std::wstring &title )
	{
		glfwSetWindowSize( (GLsizei) size[BK_X], (GLsizei) size[BK_Y] );
		glViewport( 0, 0, size[BK_X], size[BK_Y] );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0.0, (GLdouble) size[BK_X], (GLdouble) size[BK_Y], 0.0 );
		setWindowCaption( title );
	}

	void
	render( Form *form )
	{
		computeFps( mT0, mT1, mFrames, mFps );

		glClear( GL_COLOR_BUFFER_BIT );

		form->constructScene();
		form->render();

		glEnableClientState( GL_VERTEX_ARRAY );
		GraphicsNode *node = 0;
		for ( uint i = 0; i < mNodes.size(); ++i ) {
			node = mNodes[i];

			glBindBuffer( GL_ARRAY_BUFFER, node->vbo );

			// read first three bytes off of the buffer to get the colour
			GLuint colourSize = sizeof( float ) * 3;
			GLfloat *colour = static_cast<GLfloat*>( glMapBufferRange( GL_ARRAY_BUFFER, 0, colourSize, GL_MAP_READ_BIT ) );
			if ( colour )
				glColor3fv( colour );

			glVertexPointer( node->vertexCount, GL_FLOAT, 0, BUFFER_OFFSET(colourSize) );
			glDrawArrays( node->type, 0, node->indexCount );

			glBindBuffer( GL_ARRAY_BUFFER, 0 );
			glDeleteBuffers( 1, &node->vbo );
		}

		mNodes.clear();
		glDisableClientState( GL_VERTEX_ARRAY );
		glfwSwapBuffers();
	}

	float
	fps() const
	{
		return mFps;
	}

	void
	setWindowCaption( const std::wstring &title )
	{
		glfwSetWindowTitle( toString( title ).c_str() );
	}

	void
	shutdown()
	{
		glfwTerminate();
	}

	void
	drawCircle( const vec3<float> &pos, const uint radius, const Colour &c )
	{
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f( pos[BK_X], pos[BK_Y] );
			for ( float i = 0; i <= 2 * M_PI + 0.1; i += 0.1 ) {
				glVertex2f(
					pos[BK_X] + sin(i) * radius,
					pos[BK_Y] + cos(i) * radius
				);
			}
		glEnd();
	}

	void
	drawImage( const string &filePath, const vec2<float> &size, const vec3<float> &pos )
	{
		BK_DEBUG( "drawImage: implement me!!" );
	}

	void
	drawLine( const vec3<float> &from, const vec3<float> &to, const Colour &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			from[BK_X], from[BK_Y],
			to[BK_X], to[BK_Y]
		};

		GraphicsNode *node = new GraphicsNode();

		node->type = GL_POINTS;
		node->vertexCount = 2;
		node->indexCount = 2;

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawPoint( const vec3<float> &pos, const uint size, const Colour &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			pos[BK_X], pos[BK_Y]
		};

		GraphicsNode *node = new GraphicsNode();

		node->type = GL_POINTS;
		node->vertexCount = 2;
		node->indexCount = 1;

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawRect( const vec2<float> &size, const vec3<float> &pos, const Colour &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			pos[BK_X],					pos[BK_Y],
			pos[BK_X] + size[BK_WIDTH],	pos[BK_Y],
			pos[BK_X] + size[BK_WIDTH],	pos[BK_Y] + size[BK_HEIGHT],
			pos[BK_X],					pos[BK_Y] + size[BK_HEIGHT]
		};

		GraphicsNode *node = new GraphicsNode();

		node->type = GL_QUADS;
		node->vertexCount = 2;
		node->indexCount = 4;

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawText( const wchar_t *text, const vec3<float> &pos, const Colour &c )
	{
		mFont->render(
			pos,
			toString( wstring(text) ).c_str(),
			c
		);
	}

private:
	GlfwGraphics* 			mMaster;
	vector<GraphicsNode*>	mNodes;
	Font*					mFont;

	float					mT0;
	float					mT1;
	float					mFrames;
	float					mFps;
};

// }}}

GlfwGraphics::GlfwGraphics() :
	mImpl( new GlfwGraphicsP( this ) )
{
}

GlfwGraphics::~GlfwGraphics()
{
	delete mImpl;
}

int
GlfwGraphics::init( CoreServices *services )
{
	return mImpl->init( services );
}

void
GlfwGraphics::createWindow( const vec2<int> &size, const std::wstring &title )
{
	mImpl->createWindow( size, title );
}

void
GlfwGraphics::render( Form *form )
{
	mImpl->render( form );
}

void
GlfwGraphics::shutdown()
{
	mImpl->shutdown();
}

void
GlfwGraphics::loadResource( const string &path, const string &id )
{
	BK_DEBUG( "implement me!" );
}

void
GlfwGraphics::freeResource( const string &id )
{
	BK_DEBUG( "implement me!" );
}

void
GlfwGraphics::drawCircle( const vec3<float> &pos, const uint radius, const Colour &c )
{
	mImpl->drawCircle( pos, radius, c );
}

void
GlfwGraphics::drawImage( const string &filePath, const vec2<float> &size, const vec3<float> &pos )
{
}

void
GlfwGraphics::drawLine( const vec3<float> &from, const vec3<float> &to, const Colour &colour )
{
	mImpl->drawLine( from, to, colour );
}

void
GlfwGraphics::drawPoint( const vec3<float> &pos, const uint size, const Colour &colour )
{
	mImpl->drawPoint( pos, size, colour );
}

void
GlfwGraphics::drawRect( const vec2<float> &size, const vec3<float> &pos, const Colour &colour )
{
	mImpl->drawRect( size, pos, colour );
}

void
GlfwGraphics::drawText( const wchar_t *text, const vec3<float> &pos, const Colour &colour )
{
	mImpl->drawText( text, pos, colour );
}

float
GlfwGraphics::fps() const
{
	return mImpl->fps();
}

void
GlfwGraphics::setWindowCaption( const std::wstring &title )
{
	mImpl->setWindowCaption( title );
}

