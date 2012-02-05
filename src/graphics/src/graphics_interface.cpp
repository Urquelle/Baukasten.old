#include "graphics_interface.h"
#include "igraphics.h"

#include "glfw/glfw_graphics.h"

using namespace Baukasten;

IGraphics* GraphicsInterface::mInstance = 0;

IGraphics*
GraphicsInterface::instance()
{
	if ( !mInstance ) {
		mInstance = new GlfwGraphics();
	}

	return mInstance;
}

