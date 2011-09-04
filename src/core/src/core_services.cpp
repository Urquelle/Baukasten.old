#include "core_services.h"

#include "iinput.h"
#include "igraphics.h"

using namespace Baukasten;

CoreServices::CoreServices() :
	mGraphics( GraphicsInterface::instance() ),
	mInput( InputInterface::instance() )
{
}

CoreServices::~CoreServices()
{
}

void CoreServices::init( const Services &services )
{
	switch ( services ) {
	case INPUT:
		mInput->init();
		break;
	case VIDEO:
		mGraphics->init();
		break;
	case ALL:
		mInput->init();
		mGraphics->init();
		break;
	}
}

IGraphics* CoreServices::getVideoService() const
{
	return mGraphics;
}

IInput* CoreServices::getInputService() const
{
	return mInput;
}

