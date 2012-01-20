#include "core_services.h"

#include "iaudio.h"
#include "igraphics.h"
#include "iinput.h"

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
	mAudio( AudioInterface::instance() ),
	mGraphics( GraphicsInterface::instance() ),
	mInput( InputInterface::instance() )
{
}

CoreServices::~CoreServices()
{
}

void
CoreServices::init( int argc, char* argv[] )
{
	mArgc = argc;
	mArgv = argv;

	mAudio->init( this );
	mGraphics->init( this );
	mInput->init( this );
}

void
CoreServices::shutdown()
{
	mAudio->shutdown();
	mGraphics->shutdown();
	mInput->shutdown();
}

IAudio*
CoreServices::getAudioService() const
{
	return mAudio;
}

IInput*
CoreServices::getInputService() const
{
	return mInput;
}

IGraphics*
CoreServices::getVideoService() const
{
	return mGraphics;
}

int
CoreServices::getArgumentsCount()
{
	return mArgc;
}

char**
CoreServices::getArguments() const
{
	return mArgv;
}

