#include "core_services.h"

#include "iinput.h"
#include "igraphics.h"

using namespace Baukasten;

CoreServices* CoreServices::mInstance = 0;

CoreServices*
CoreServices::instance()
{
	if ( !mInstance )
		mInstance = new CoreServices();
	return mInstance;
}

CoreServices::CoreServices() :
	mGraphics( GraphicsInterface::instance() ),
	mInput( InputInterface::instance() )
{
}

CoreServices::~CoreServices()
{
}

void
CoreServices::init()
{
	mGraphics->init( this );
	mInput->init( this );
}

IGraphics*
CoreServices::getVideoService() const
{
	return mGraphics;
}

IInput*
CoreServices::getInputService() const
{
	return mInput;
}

