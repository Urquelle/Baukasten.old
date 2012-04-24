#ifndef GLFW_GRAPHICS_FUNCTIONS_H_SRTQPXNJ
#define GLFW_GRAPHICS_FUNCTIONS_H_SRTQPXNJ

#include "core/TimerInterface"
#include "core/Timer"
#include "graphics/Font"
#include "graphics/Global"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <cmath>

using namespace Baukasten;

const char *_bk_vertex_shader (
	"#version 120\n"

	"attribute vec4 position;\n"
	"attribute vec4 color;\n"

	"void main()\n"
	"{\n"
	"   gl_Position = position;\n"
	"	gl_FrontColor = color;\n"
	"}\n"
);

const char *_bk_fragment_shader (
	"#version 120\n"

	"void main()\n"
	"{\n"
	"   gl_FragColor = gl_Color;\n"
	"}\n"
);

static f32
_normalise( const int size, const f32 i )
{
	f32 div = size / 2;
	return ( i - div ) / div;
}

static void GLFWCALL
_resize( int width, int height )
{
	Services::instance().graphicsService().setWindowSize( width, height );
}

static GLuint
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

static bool
_initProgram( GLuint &program )
{
	GLuint vertexShader = _createShader( GL_VERTEX_SHADER, _bk_vertex_shader );
	GLuint fragmentShader = _createShader( GL_FRAGMENT_SHADER, _bk_fragment_shader );

	program = glCreateProgram();

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

static inline void
_computeFps( f32 &t0, f32 &t1, u32 &frames, f32 &fps )
{
	t1 = TimerInterface::instance()->timer( "system:main" ).time();

	if ( ( t1 - t0 ) >= 1.0 || frames == 0 ) {
		fps = frames / ( t1 - t0 );
		t0 = t1;
		frames = 0;
	}

	frames++;
}

#endif /* end of include guard: GLFW_GRAPHICS_FUNCTIONS_H_SRTQPXNJ */

