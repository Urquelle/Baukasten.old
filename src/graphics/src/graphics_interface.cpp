#include "graphics_interface.h"
#include "igraphics.h"

#if defined(WITH_OGRE)
#	include "ogre/ogre_interface.h"
#else
#	include "irrlicht/irrlicht_graphics.h"
#endif

using namespace Baukasten;

IGraphics* GraphicsInterface::mInstance = 0;

IGraphics* GraphicsInterface::instance()
{
	if ( !mInstance ) {
#if defined(WITH_OGRE)
		mInstance = new OgreInterface();
#else
		mInstance = new IrrlichtGraphics();
#endif
	}

	return mInstance;
}

