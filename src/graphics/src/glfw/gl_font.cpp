#include "graphics/include/glfw/gl_font.h"

#include "core/Debug"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace Baukasten;

const char *f_shader_data =
"#version 120\n"

"varying vec2 texpos;\n"
"uniform sampler2D tex;\n"
"uniform vec4 color;\n"

"void main(void) {\n"
"	gl_FragColor = vec4(1, 1, 1, texture2D(tex, texpos).a) * color;\n"
"}\n";

const char *v_shader_data =
"#version 120\n"

"attribute vec4 coord;\n"
"varying vec2 texpos;\n"

"void main(void) {\n"
"	gl_Position = vec4(coord.xy, 0, 1);\n"
"	texpos = coord.zw;\n"
"}\n";

struct point
{
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

GLuint create_fragment_shader(GLenum type)
{
	const GLchar* source = f_shader_data;
	GLuint res = glCreateShader(type);
	glShaderSource(res, 1, &source, NULL);

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);

	return res;
}

GLuint create_vertex_shader(GLenum type)
{
	const GLchar* source = v_shader_data;
	GLuint res = glCreateShader(type);
	glShaderSource(res, 1, &source, NULL);

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);

	return res;
}

class Baukasten::GlFontPrivate {
public:

	struct atlas
	{
		GLuint tex;    // texture object

		float w; // width of texture in pixels
		float h; // height of texture in pixels

		struct
		{
			float ax; // advance.x
			float ay; // advance.y

			float bw; // bitmap.width;
			float bh; // bitmap.height;

			float bl; // bitmap_left;
			float bt; // bitmap_top;

			float tx; // x offset of glyph in texture coordinates
		} c[128]; // character information

		atlas(FT_Face face, int height)
		{
			FT_Set_Pixel_Sizes(face, 0, height);
			FT_GlyphSlot g = face->glyph;

			int minw = 0;
			int minh = 0;

			memset(c, 0, sizeof c);

			/* Find minimum size for a texture holding all visible ASCII characters */
			for(int i = 32; i < 128; i++) {
				if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
					fprintf(stderr, "Loading character %c failed!\n", i);
					continue;
				}
				minw += g->bitmap.width + 1;
				minh = std::max(minh, g->bitmap.rows);
			}

			w = minw;
			h = minh;

			/* Create a texture that will be used to hold all ASCII glyphs */
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, minw, minh, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);

			/* We require 1 byte alignment when uploading texture data */
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			/* Clamping to edges is important to prevent artifacts when scaling */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			/* Linear filtering usually looks best for text */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			/* Paste all glyph bitmaps into the texture, remembering the offset */
			int o = 0;

			for(int i = 32; i < 128; i++) {
				if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
					fprintf(stderr, "Loading character %c failed!\n", i);
					continue;
				}

				glTexSubImage2D(GL_TEXTURE_2D, 0, o, 0, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
				c[i].ax = g->advance.x >> 6;
				c[i].ay = g->advance.y >> 6;

				c[i].bw = g->bitmap.width;
				c[i].bh = g->bitmap.rows;

				c[i].bl = g->bitmap_left;
				c[i].bt = g->bitmap_top;

				c[i].tx = o / w;

				o += g->bitmap.width + 1;
			}

			glGenerateMipmap(GL_TEXTURE_2D);
			fprintf(stderr, "Generated a %d x %d (%d kb) texture atlas\n", minw, minh, minw * minh / 1024);
		}

		~atlas()
		{
			glDeleteTextures(1, &tex);
		}
	};

	~GlFontPrivate()
	{
		glDeleteProgram(program);
	}

	GlFontPrivate( const string &path, const u32 size )
	{
		/* Initialize the FreeType2 library */
		if(FT_Init_FreeType(&ft)) {
			fprintf(stderr, "Could not init freetype library\n");
			return;
		}

		/* Load a font */
		if(FT_New_Face(ft, path.c_str(), 0, &face)) {
			BK_DEBUG( "Could not open font " << path );
			return;
		}

		/* Create texture atlasses for several font sizes */
		m_atlas = new atlas(face, size);

		/* Compile and link the shader program */
		GLint link_ok = GL_FALSE;

		GLuint vs, fs;
		if ((vs = create_vertex_shader(GL_VERTEX_SHADER))	 == 0) return;
		if ((fs = create_fragment_shader(GL_FRAGMENT_SHADER)) == 0) return;

		program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
		if (!link_ok) {
			fprintf(stderr, "glLinkProgram:");
			return;
		}

		const char* attribute_name;
		attribute_name = "coord";
		attribute_coord = glGetAttribLocation(program, attribute_name);
		if (attribute_coord == -1) {
			fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
			return;
		}

		const char* uniform_name;
		uniform_name = "tex";
		uniform_tex = glGetUniformLocation(program, uniform_name);
		if (uniform_tex == -1) {
			fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
			return;
		}

		uniform_name = "color";
		uniform_color = glGetUniformLocation(program, uniform_name);
		if (uniform_color == -1) {
			fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
			return;
		}

		// Create the vertex buffer object
		glGenBuffers(1, &vbo);

		return;
	}

	void render(const char *text, atlas *a, float x,
			float y, float sx, float sy, const Color &col)
	{
		glUseProgram(program);

		/* Enable blending, necessary for our alpha texture */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/* Set color to black */
		GLfloat color[4] = { col.redF(), col.greenF(), col.blueF(), col.alphaF() };
		glUniform4fv(uniform_color, 1, color );

		const uint8_t *p;

		/* Use the texture containing the atlas */
		glBindTexture(GL_TEXTURE_2D, a->tex);
		glUniform1i(uniform_tex, 0);

		/* Set up the VBO for our vertex data */
		glEnableVertexAttribArray(attribute_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

		point coords[6 * strlen(text)];
		int c = 0;

		/* Loop through all characters */
		for ( p = (const uint8_t *)text; *p; p++ ) {
			/* Calculate the vertex and texture coordinates */
			float x2 =  x + a->c[*p].bl * sx;
			float y2 = -y - a->c[*p].bt * sy;
			float w = a->c[*p].bw * sx;
			float h = a->c[*p].bh * sy;

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

		glDisableVertexAttribArray(attribute_coord);
		glUseProgram(0);
	}

	void display( const string &text, const vec3<float> &pos, const Color &c )
	{
		int width, height;
		glfwGetWindowSize( &width, &height );
		float sx = 2.0 / width;
		float sy = 2.0 / height;

		float x = ( pos[BK_X] - width / 2 ) / ( width / 2 );
		float y = ( pos[BK_Y] - height / 2 ) / ( height / 2 ) * -1;

		render( text.c_str(), m_atlas, x, y, sx, sy, c );
	}

private:
	GLuint program;
	GLint attribute_coord;
	GLint uniform_tex;
	GLint uniform_color;
	GLuint vbo;

	FT_Library ft;
	FT_Face face;

	atlas *m_atlas;
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
GlFont::render( const string &text, const vec3<float> &pos, const Color &c )
{
	m_impl->display( text, pos, c );
}

