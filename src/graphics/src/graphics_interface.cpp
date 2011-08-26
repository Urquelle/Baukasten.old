#include "graphics_interface.h"
#include "igraphics.h"

#if defined(WITH_OGRE)
#	include "ogre/ogre_interface.h"
#endif

using namespace Baukasten;

GraphicsInterface* GraphicsInterface::mInstance = 0;

GraphicsInterface* GraphicsInterface::instance()
{
	if ( !mInstance )
		mInstance = new GraphicsInterface();
	return mInstance;
}

GraphicsInterface::GraphicsInterface() :
	mInitialised( false ),
	mImpl( 0 )
{
}

GraphicsInterface::~GraphicsInterface()
{
	delete mInstance;
}

void GraphicsInterface::init()
{
#if defined(WITH_OGRE)
	mImpl = new OgreInterface();
#endif

	if ( mImpl ) {
		mImpl->init();
		mInitialised = true;
	}
}

void GraphicsInterface::renderForm( Form *form )
{
	if ( !mInitialised )
		init();
}

