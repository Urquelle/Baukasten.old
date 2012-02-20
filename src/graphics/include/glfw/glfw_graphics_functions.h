#ifndef GLFW_GRAPHICS_FUNCTIONS_H_SRTQPXNJ
#define GLFW_GRAPHICS_FUNCTIONS_H_SRTQPXNJ

#include "graphics/Global"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <cmath>

using namespace Baukasten;

const char *_bk_vertex_shader (
	"#version 120\n"

	"attribute vec4 position;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = position;\n"
	"}\n"
);

const char *_bk_fragment_shader (
	"#version 120\n"

	"void main()\n"
	"{\n"
	"   gl_FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n"
);

bool
_init()
{
	if ( !glfwInit() ) {
		return 0;
	}

	glfwOpenWindow( 640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
	glViewport( 0, 0, 640.0, 480.0 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glewInit();

	return true;
}

GLuint
_createShader( GLenum type, const char *shaderData )
{
	GLuint shader = glCreateShader( type );
	glShaderSource( shader, 1, &shaderData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch( type ) {
		case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
		case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
		case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
		}

		BK_DEBUG("Compile failure in " << type << " shader:\n" << strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

bool
_initProgram( GLuint *prog )
{
	GLuint vertexShader = _createShader( GL_VERTEX_SHADER, _bk_vertex_shader );
	GLuint fragmentShader = _createShader( GL_FRAGMENT_SHADER, _bk_fragment_shader );

	GLuint program = *prog = glCreateProgram();

	glAttachShader( program, vertexShader );
	glAttachShader( program, fragmentShader );

	glLinkProgram( program );

	GLint status;
	glGetProgramiv( program, GL_LINK_STATUS, &status );
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	glDetachShader( program, vertexShader );
	glDetachShader( program, fragmentShader );
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	return true;
}

string
_toString( const wstring &s )
{
	string str( s.begin(), s.end() );
	str.assign( s.begin(), s.end() );
	return str;
}

void
_checkForError()
{
	GLuint errCode = glGetError();
	if ( errCode != GL_NO_ERROR ) {
		BK_DEBUG( gluErrorString( errCode ) );
	}
}

void
_computeFps( float &t0, float &t1, float &frames, float &fps )
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
_texture( const string &source, vector<GlTexture*> *textures )
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

#endif /* end of include guard: GLFW_GRAPHICS_FUNCTIONS_H_SRTQPXNJ */

