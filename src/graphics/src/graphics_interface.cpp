#include "graphics/GraphicsInterface"

#include "graphics/GraphicsImpl"
#include "graphics/IGraphics"

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

