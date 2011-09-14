#include "irrlicht/irrlicht_graphics.h"

#include <form.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;

IrrlichtGraphics::IrrlichtGraphics() :
	IGraphics(),
	mDevice( 0 ),
	mDriver( 0 ),
	mSceneManager( 0 ),
	mGui( 0 )
{
}

IrrlichtGraphics::~IrrlichtGraphics()
{
}

int IrrlichtGraphics::init( CoreServices *coreServices )
{
	mDevice = createDevice(
		EDT_OPENGL,
		dimension2d<u32>(1024, 768),
		16, false, false, false, 0
	);

	mDriver			= mDevice->getVideoDriver();
	mSceneManager	= mDevice->getSceneManager();
	mGui			= mDevice->getGUIEnvironment();

	return 1;
}

void IrrlichtGraphics::render( Form *form )
{
	mDevice->run();
	mDriver->beginScene(true, true, video::SColor(0, 0, 0, 0));
	form->render();
	mGui->drawAll();
	mDriver->endScene();
}

void IrrlichtGraphics::shutDown()
{
	mDevice->drop();
}

void IrrlichtGraphics::setWindowCaption( const std::wstring &caption )
{
	mDevice->setWindowCaption( caption.c_str() );
}

IrrlichtDevice* IrrlichtGraphics::getDevice() const
{
	return mDevice;
}

IVideoDriver* IrrlichtGraphics::getDriver() const
{
	return mDriver;
}

ISceneManager* IrrlichtGraphics::getSceneManager() const
{
	return mSceneManager;
}

IGUIEnvironment* IrrlichtGraphics::getGui() const
{
	return mGui;
}

