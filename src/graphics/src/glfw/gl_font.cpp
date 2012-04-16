#include "graphics/include/glfw/gl_font.h"

#include "core/Debug"
#include "graphics/include/glfw/gl_font_helper.h"

using namespace Baukasten;

class Baukasten::GlFontPrivate {
public:

	~GlFontPrivate()
	{
		glDeleteProgram( m_program );
		delete m_atlas;
	}

	GlFontPrivate( const string &path, const u32 size )
	{
		init( path, size );
		return;
	}

	void render(const char *text, _atlas *a, f32 x,
			f32 y, f32 sx, f32 sy, const Color &col)
	{
		glUseProgram( m_program );

		/* Enable blending, necessary for our alpha texture */
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		GLfloat color[4] = { col.redF(), col.greenF(), col.blueF(), col.alphaF() };
		glUniform4fv( m_uniformColor, 1, color );

		const uint8_t *p;

		/* Use the texture containing the atlas */
		glBindTexture( GL_TEXTURE_2D, a->tex );
		glUniform1i( m_uniformTex, 0 );

		/* Set up the VBO for our vertex data */
		glEnableVertexAttribArray( m_attributeCoord );
		glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
		glVertexAttribPointer( m_attributeCoord, 4, GL_FLOAT, GL_FALSE, 0, 0 );

		point coords[6 * strlen(text)];
		int c = 0;

		/* Loop through all characters */
		for ( p = (const uint8_t *)text; *p; p++ ) {
			/* Calculate the vertex and texture coordinates */
			f32 x2 =  x + a->c[*p].bl * sx;
			f32 y2 = -y - a->c[*p].bt * sy;
			f32 w = a->c[*p].bw * sx;
			f32 h = a->c[*p].bh * sy;

			/* Advance the cursor to the start of the next character */
			x += a->c[*p].ax * sx;
			y += a->c[*p].ay * sy;

			/* Skip glyphs that have no pixels */
			if(!w || !h)
				continue;

			coords[c++] = (point){x2,     -y2    , a->c[*p].tx,                      0};
			coords[c++] = (point){x2 + w, -y2    , a->c[*p].tx + a->c[*p].bw / a->w, 0};
			coords[c++] = (point){x2,     -y2 - h, a->c[*p].tx,                      a->c[*p].bh / a->h};
			coords[c++] = (point){x2 + w, -y2    , a->c[*p].tx + a->c[*p].bw / a->w, 0};
			coords[c++] = (point){x2,     -y2 - h, a->c[*p].tx,                      a->c[*p].bh / a->h};
			coords[c++] = (point){x2 + w, -y2 - h, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].bh / a->h};
		}

		/* Draw all the character on the screen in one go */
		glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, c);

		glDisableVertexAttribArray( m_attributeCoord );
		glUseProgram( 0 );
	}

	void display( const string &text, const Vector3 &pos, const Color &c )
	{
		int width, height;
		glfwGetWindowSize( &width, &height );
		f32 sx = 2.0 / width;
		f32 sy = 2.0 / height;

		f32 x = ( pos[BK_X] - width / 2 ) / ( width / 2 );
		f32 y = ( pos[BK_Y] - height / 2 ) / ( height / 2 ) * -1;

		render( text.c_str(), m_atlas, x, y, sx, sy, c );
	}

	void
	setSize( const u32 size )
	{
		if ( this->size() == size ) return;
		delete m_atlas;
		m_atlas = new _atlas( m_face, size );
	}

	u32
	size() const
	{
		// FreeType stores the size in its own way:
		//
		// The character widths and heights are specified in 1/64th of points.
		// A point is a physical distance, equaling 1/72th of an inch. Normally,
		// it is not equivalent to a pixel.
		return static_cast<u32>( m_face->size->metrics.height / 72 );
	}

	void
	setFont( const string &path )
	{
		if ( path == m_path ) return;
		delete m_atlas;
		init( path, size() );
	}

	string
	font() const
	{
		return m_path;
	}

private:
	void init( const string &path, const u32 size )
	{
		m_path = path;
		_initFreeType( m_lib, m_face, path );
		m_atlas = new _atlas( m_face, size );
		_constructGlProgram( m_program, m_attributeCoord,
				m_uniformTex, m_uniformColor, m_vbo );
	}

	_atlas*     m_atlas;
	GLint       m_attributeCoord;
	FT_Face     m_face;
	FT_Library  m_lib;
	string      m_path;
	GLuint      m_program;
	GLint       m_uniformColor;
	GLint       m_uniformTex;
	GLuint      m_vbo;
};

GlFont::GlFont( const string &path ) :
	m_impl( new GlFontPrivate( path, 12 ) )
{
}

GlFont::GlFont( const string &path, const u32 size ) :
	m_impl( new GlFontPrivate( path, size ) )
{
}

GlFont::~GlFont()
{
	delete m_impl;
}

void
GlFont::render( const string &text, const Vector3 &pos, const Color &c )
{
	m_impl->display( text, pos, c );
}

void
GlFont::setSize( const u32 size )
{
	m_impl->setSize( size );
}

u32
GlFont::size() const
{
	return m_impl->size();
}

void
GlFont::setFont( const string &path )
{
	m_impl->setFont( path );
}

string
GlFont::font() const
{
	return m_impl->font();
}

