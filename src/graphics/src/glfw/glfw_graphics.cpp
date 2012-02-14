#include "graphics/GraphicsImpl"

#include "core/Font"
#include "model/CoreServices"
#include "model/Form"
#include "graphics/include/glfw/node.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glfw.h>

#include <cmath>
#include <cstring>
#include <vector>

#define BUFFER_OFFSET(offset) ((char*) NULL + offset)

string
toString( const wstring &s )
{
	string str( s.begin(), s.end() );
	str.assign( s.begin(), s.end() );
	return str;
}

void
checkForError()
{
	GLuint errCode = glGetError();
	if ( errCode != GL_NO_ERROR ) {
		BK_DEBUG( gluErrorString( errCode ) );
	}
}

void
computeFps( float &t0, float &t1, float &frames, float &fps )
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
		for ( int32 i = 0; i < mNodes.size(); ++i ) {
			mNodes[i]->render();
		}
		glDisableClientState( GL_VERTEX_ARRAY );

		mNodes.clear();

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
	drawCircle( const vec3<float> &pos, const int32 radius, const Color &c )
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
	drawLine( const vec3<float> &from, const vec3<float> &to, const Color &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			from[BK_X], from[BK_Y],
			to[BK_X], to[BK_Y]
		};

		LineNode *node = new LineNode( GL_POINTS, 2, 2 );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawPoint( const vec3<float> &pos, const int32 size, const Color &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			pos[BK_X], pos[BK_Y]
		};

		PointNode *node = new PointNode( GL_POINTS, 2, 1 );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawRect( const vec2<float> &size, const vec3<float> &pos, const Color &c )
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

		QuadNode *node = new QuadNode( GL_QUADS, 2, 4 );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawText( const wchar_t *text, const vec3<float> &pos, const Color &c )
	{
		mFont->render(
			pos,
			toString( wstring(text) ).c_str(),
			c
		);
	}

private:
	float					mT0;
	float					mT1;
	float					mFrames;
	float					mFps;
	GlfwGraphics*		mMaster;
	vector<Node*>		mNodes;
	Font*				mFont;
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
GlfwGraphics::drawCircle( const vec3<float> &pos, const int32 radius, const Color &c )
{
	mImpl->drawCircle( pos, radius, c );
}

void
GlfwGraphics::drawImage( const string &filePath, const vec2<float> &size, const vec3<float> &pos )
{
}

void
GlfwGraphics::drawLine( const vec3<float> &from, const vec3<float> &to, const Color &color )
{
	mImpl->drawLine( from, to, color );
}

void
GlfwGraphics::drawPoint( const vec3<float> &pos, const int32 size, const Color &color )
{
	mImpl->drawPoint( pos, size, color );
}

void
GlfwGraphics::drawRect( const vec2<float> &size, const vec3<float> &pos, const Color &color )
{
	mImpl->drawRect( size, pos, color );
}

void
GlfwGraphics::drawText( const wchar_t *text, const vec3<float> &pos, const Color &color )
{
	mImpl->drawText( text, pos, color );
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

