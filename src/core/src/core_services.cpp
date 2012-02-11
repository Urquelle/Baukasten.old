#include "core/CoreServices"

#include "core/Debug"
#include "audio/IAudio"
#include "graphics/IGraphics"
#include "input/IInput"

using namespace Baukasten;

CoreServices*
CoreServices::instance()
{
	static CoreServices instance;
	return &instance;
}

CoreServices::CoreServices() :
	mAudio( AudioInterface::instance() ),
	mGraphics( GraphicsInterface::instance() ),
	mInput( InputInterface::instance() )
{
}

CoreServices::~CoreServices()
{
	BK_DEBUG( "destroy CoreServices" );
	mAudio->shutdown();
	mGraphics->shutdown();
	mInput->shutdown();
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
	mInput->shutdown();
	mGraphics->shutdown();
	mAudio->shutdown();
}

IAudio*
CoreServices::audioService() const
{
	return mAudio;
}

IInput*
CoreServices::inputService() const
{
	return mInput;
}

IGraphics*
CoreServices::videoService() const
{
	return mGraphics;
}

int
CoreServices::argumentsCount()
{
	return mArgc;
}

char**
CoreServices::arguments() const
{
	return mArgv;
}

