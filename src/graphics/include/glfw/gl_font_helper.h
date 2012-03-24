#ifndef GL_FONT_HELPER_H_8JCDTH0M
#define GL_FONT_HELPER_H_8JCDTH0M

#include <GL/glew.h>
#include <GL/glfw.h>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

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

struct point {
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

struct _atlas
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

	_atlas(FT_Face face, int height)
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
	}

	~_atlas()
	{
		glDeleteTextures(1, &tex);
	}
};

void _initFreeType( FT_Library &lib, FT_Face &face, const string &path )
{
	if ( FT_Init_FreeType( &lib ) ) {
		BK_DEBUG( "Could not init freetype library." );
		return;
	}

	if ( FT_New_Face( lib, path.c_str(), 0, &face ) ) {
		BK_DEBUG( "Could not open font " << path );
		return;
	}
}

void _constructGlProgram( GLuint &program, GLint &attribute_coord,
		GLint &uniform_tex, GLint &uniform_color, GLuint &vbo )
{
	/* Compile and link the shader program */
	GLint link_ok = GL_FALSE;

	GLuint vs, fs;
	if ((vs = create_vertex_shader(GL_VERTEX_SHADER)) == 0) return;
	if ((fs = create_fragment_shader(GL_FRAGMENT_SHADER)) == 0) return;

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		BK_DEBUG( "Could not link Program" );
		return;
	}

	const char* attribute_name;
	attribute_name = "coord";
	attribute_coord = glGetAttribLocation(program, attribute_name);
	if (attribute_coord == -1) {
		BK_DEBUG( "Could not bind attribute " << attribute_name );
		return;
	}

	const char* uniform_name;
	uniform_name = "tex";
	uniform_tex = glGetUniformLocation(program, uniform_name);
	if (uniform_tex == -1) {
		BK_DEBUG( "Could not bind uniform " << uniform_name );
		return;
	}

	uniform_name = "color";
	uniform_color = glGetUniformLocation(program, uniform_name);
	if (uniform_color == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		BK_DEBUG( "Could not bind uniform " << uniform_name );
		return;
	}

	// Create the vertex buffer object
	glGenBuffers(1, &vbo);

}

#endif /* end of include guard: GL_FONT_HELPER_H_8JCDTH0M */

