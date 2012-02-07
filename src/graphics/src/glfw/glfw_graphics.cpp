#include "glfw/glfw_graphics.h"
#include "font.h"

#include "core_services.h"
#include "form.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glfw.h>

#include <cmath>
#include <cstring>
#include <vector>

string toString( const wstring &s )
{
	string str( s.begin(), s.end() );
	str.assign( s.begin(), s.end() );
	return str;
}

using namespace Baukasten;

// GlfGraphicsP {{{

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
		if ( !glfwInit() ) {
			return 0;
		}

		glfwOpenWindow( 640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
		glViewport( 0, 0, 640.0, 480.0 );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0.0, 640.0, 480.0, 0.0 );

		mMaster->mInitialised = true;

		return 1;
	}

	void createWindow( const v2<int> &size, const std::wstring &title )
	{
		glfwSetWindowSize( (GLsizei) size.getX(), (GLsizei) size.getY() );
		glViewport( 0, 0, size.getX(), size.getY() );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0.0, (GLdouble) size.getX(), (GLdouble) size.getY(), 0.0 );
		setWindowCaption( title );
	}

	void
	render( Form *form )
	{
		glClear( GL_COLOR_BUFFER_BIT );

		form->draw();
		form->render();

		glfwSwapBuffers();
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
	drawCircle( const v3<float> &pos, const uint radius, const Colour &c )
	{
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f( pos.getX(), pos.getY() );
			for ( float i = 0; i <= 2 * M_PI + 0.1; i += 0.1 ) {
				glVertex2f(
					pos.getX() + sin(i) * radius,
					pos.getY() + cos(i) * radius
				);
			}
		glEnd();
	}

	void
	drawImage( const string &filePath, const v2<float> &size, const v3<float> &pos )
	{
		BK_DEBUG( "drawImage: implement me!!" );
	}

	void
	drawLine( const v3<float> &from, const v3<float> &to, const Colour &c )
	{
		float r, g, b;
		c.getRgbF( &r, &g, &b );

		glColor3f( r, g, b );
		glBegin( GL_LINES );
			glVertex3f( from.getX(), from.getY(), from.getZ() );
			glVertex3f( to.getX(), to.getY(), to.getZ() );
		glEnd();
	}

	void
	drawPoint( const v3<float> &pos, const uint size, const Colour &c )
	{
		float r, g, b;
		c.getRgbF( &r, &g, &b );

		glColor3f( r, g, b );
		glPointSize( size );
		glBegin( GL_POINTS );
			glVertex3f( pos.getX(), pos.getY(), pos.getZ() );
		glEnd();
	}

	void
	drawRect( const v2<float> &size, const v3<float> &pos, const Colour &c )
	{
		float r, g, b;
		c.getRgbF( &r, &g, &b );

		glColor3f( r, g, b );
		glRectf(
			pos.getX(), pos.getY(),
			pos.getX() + size.getX(), pos.getY() + size.getY()
		);
	}

	void
	drawText( const wchar_t *text, const v3<float> &pos, const Colour &c )
	{
		mFont->render(
			pos,
			toString( wstring(text) ).c_str(),
			c
		);
	}

private:
	GlfwGraphics* 	mMaster;
	Font*			mFont;
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
GlfwGraphics::createWindow( const v2<int> &size, const std::wstring &title )
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
GlfwGraphics::drawCircle( const v3<float> &pos, const uint radius, const Colour &c )
{
	mImpl->drawCircle( pos, radius, c );
}

void
GlfwGraphics::drawImage( const string &filePath, const v2<float> &size, const v3<float> &pos )
{
}

void
GlfwGraphics::drawLine( const v3<float> &from, const v3<float> &to, const Colour &colour )
{
	mImpl->drawLine( from, to, colour );
}

void
GlfwGraphics::drawPoint( const v3<float> &pos, const uint size, const Colour &colour )
{
	mImpl->drawPoint( pos, size, colour );
}

void
GlfwGraphics::drawRect( const v2<float> &size, const v3<float> &pos, const Colour &colour )
{
	mImpl->drawRect( size, pos, colour );
}

void
GlfwGraphics::drawText( const wchar_t *text, const v3<float> &pos, const Colour &colour )
{
	mImpl->drawText( text, pos, colour );
}

void
GlfwGraphics::setWindowCaption( const std::wstring &title )
{
	mImpl->setWindowCaption( title );
}

