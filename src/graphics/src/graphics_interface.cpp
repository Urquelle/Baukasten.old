#include "graphics_interface.h"
#include "igraphics.h"

#include "irrlicht/irrlicht_graphics.h"

using namespace Baukasten;

IGraphics* GraphicsInterface::mInstance = 0;

IGraphics*
GraphicsInterface::instance()
{
	if ( !mInstance ) {
		mInstance = new IrrlichtGraphics();
	}

	return mInstance;
}

