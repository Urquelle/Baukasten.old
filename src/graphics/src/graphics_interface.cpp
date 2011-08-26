#include "graphics_interface.h"

using namespace Baukasten;

GraphicsInterface* GraphicsInterface::mInstance = 0;

GraphicsInterface* GraphicsInterface::instance()
{
	if ( !mInstance )
		mInstance = new GraphicsInterface();
	return mInstance;
}

GraphicsInterface::GraphicsInterface()
{
}

GraphicsInterface::~GraphicsInterface()
{
}

