#include "graphics_interface.h"

using namespace Baukasten;

GraphicsInterface* GraphicsInterface::mInstance = 0;

GraphicsInterface* GraphicsInterface::instance()
{
	if ( !mInstance )
		mInstance = new GraphicsInterface();
	return mInstance;
}

GraphicsInterface::GraphicsInterface() :
	mInitialised( false )
{
}

GraphicsInterface::~GraphicsInterface()
{
	delete mInstance;
}

void GraphicsInterface::init()
{
}

void GraphicsInterface::renderForm( Form *form )
{
	if ( !mInitialised )
		init();
}

