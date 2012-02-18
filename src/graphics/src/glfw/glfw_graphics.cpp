#include "graphics/GraphicsImpl"

#include "core/CoreServices"
#include "core/Font"
#include "graphics/Image"
#include "graphics/include/glfw/gl_texture.h"
#include "model/Form"

#include "graphics/include/glfw/node.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <cmath>

using namespace Baukasten;

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

GlTexture*
texture( const string &source, vector<GlTexture*> *textures )
{
	GlTexture *tex = 0;
	for ( s32 i = 0; i < textures->size(); ++i ) {
		GlTexture *t = textures->at(i);
		if ( t && t->source() == source ) {
			tex = t;
			break;
		}
	}

	return tex;
}


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
		mT0 = glfwGetTime();

		if ( !glfwInit() ) {
			return 0;
		}

		glfwOpenWindow( 640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
		glViewport( 0, 0, 640.0, 480.0 );
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
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		for ( s32 i = 0; i < mNodes.size(); ++i ) {
			mNodes[i]->render();
		}
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );

		mNodes.clear();

		glfwSwapBuffers();
		BK_DEBUG( "fps: " << fps() );
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
	drawCircle( const vec3<float> &pos, const u32 radius, const Color &c )
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
	drawImage( const string &filePath, const vec2<float> &size,
			const vec3<float> &pos )
	{
		float xMin = pos[BK_X], xMax = pos[BK_X] + size[BK_WIDTH];
		float yMin = pos[BK_Y], yMax = pos[BK_Y] + size[BK_HEIGHT];

		GLfloat vertices[] = {
			// color
			0.0f, 0.0f, 0.0f,

			// vertices
			xMin, yMin,
			xMax, yMin,
			xMax, yMax,
			xMin, yMax
		};

		GlTexture *tex = texture( filePath, &mTextures );
		if ( !tex ) {
			float divX = size[BK_WIDTH];
			float divY = size[BK_HEIGHT];

			GLfloat texCoords[] = {
				xMin / divX, yMin / divY,
				xMax / divX, yMin / divY,
				xMax / divX, yMax / divY,
				xMin / divX, yMax / divY
			};

			Image image( filePath );
			image.read();

			tex = new GlTexture( filePath, size );

			// upload texture data
			glEnable( GL_TEXTURE_2D );
			glGenTextures( 1, &tex->tbo );
			glBindTexture( GL_TEXTURE_2D, tex->tbo );
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

			glTexImage2D(
				GL_TEXTURE_2D, 0, GL_RGBA8,
				image.width(), image.height(), 0, GL_RGBA8,
				GL_UNSIGNED_SHORT, image.data()
			);

			// upload texture coordinates
			glGenBuffers( 1, &tex->cbo );
			glBindBuffer( GL_ARRAY_BUFFER, tex->cbo );
			glBufferData( GL_ARRAY_BUFFER, sizeof( texCoords ), texCoords, GL_DYNAMIC_DRAW );
			glBindBuffer( GL_ARRAY_BUFFER, 0 );
		}

		QuadNode *node = new QuadNode( GL_QUADS, 2, 4 );

		node->addTexture( tex );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
		mTextures.push_back( tex );
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

		mNodes.push_back( node );
	}

	void
	drawPoint( const vec3<float> &pos, const u32 size, const Color &c )
	{
		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			pos[BK_X], pos[BK_Y]
		};

		PointNode *node = new PointNode( GL_POINTS, 2, 1 );

		node->setSize( size );

		glGenBuffers( 1, &node->vbo );
		glBindBuffer( GL_ARRAY_BUFFER, node->vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		mNodes.push_back( node );
	}

	void
	drawRect( const vec2<float> &size, const vec3<float> &pos, const Color &c )
	{
		float xMin = pos[BK_X], xMax = pos[BK_X] + size[BK_WIDTH];
		float yMin = pos[BK_Y], yMax = pos[BK_Y] + size[BK_HEIGHT];

		float r, g, b;
		c.rgbF( &r, &g, &b );

		GLfloat vertices[] = {
			r, g, b,
			xMin, yMin,
			xMax, yMin,
			xMax, yMax,
			xMin, yMax
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
	GlfwGraphics*		mMaster;
	vector<Node*>		mNodes;
	vector<GlTexture*>	mTextures;
	Font*				mFont;

	float				mT0, mT1, mFrames, mFps;
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
GlfwGraphics::drawCircle( const vec3<float> &pos, const u32 radius,
		const Color &c )
{
	mImpl->drawCircle( pos, radius, c );
}

void
GlfwGraphics::drawImage( const string &filePath, const vec2<float> &size,
		const vec3<float> &pos )
{
	mImpl->drawImage( filePath, size, pos );
}

void
GlfwGraphics::drawLine( const vec3<float> &from, const vec3<float> &to,
		const Color &color, const float width )
{
	mImpl->drawLine( from, to, color, width );
}

void
GlfwGraphics::drawPoint( const vec3<float> &pos,
		const u32 size, const Color &color )
{
	mImpl->drawPoint( pos, size, color );
}

void
GlfwGraphics::drawRect( const vec2<float> &size,
		const vec3<float> &pos, const Color &color )
{
	mImpl->drawRect( size, pos, color );
}

void
GlfwGraphics::drawText( const wchar_t *text, const vec3<float> &pos,
		const Color &color )
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

