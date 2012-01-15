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

int
IrrlichtGraphics::init( CoreServices *coreServices )
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

void
IrrlichtGraphics::render( Form *form )
{
	mDevice->run();
	mDriver->beginScene(true, true, video::SColor(0, 0, 0, 0));
	form->draw();
	mSceneManager->drawAll();
	mGui->drawAll();
	mDriver->endScene();
}

void
IrrlichtGraphics::shutDown()
{
	mDevice->drop();
}

void
IrrlichtGraphics::drawImage( const std::string &filePath, const t_size &size, const t_pos &pos )
{
	irr::video::ITexture* mBackground = mDriver->getTexture( filePath.c_str() );
	mDriver->draw2DImage(
		mBackground,
		core::position2d<s32>( pos.getX(), pos.getY() ),
		core::rect<s32>(0, 0, size.width, size.height),
		0, video::SColor(255,255,255,255), true
	);
}

void
IrrlichtGraphics::drawLine( const t_pos &from, const t_pos &to, const Colour &colour )
{
	irr::video::SColor iColour( colour.getR(), colour.getG(), colour.getB(), colour.getAlpha() );

	mDriver->draw2DLine(
		irr::core::position2d<s32>( from.getX(), from.getY() ),
		irr::core::position2d<s32>( to.getX(), to.getY() ),
		iColour
	);
}

void
IrrlichtGraphics::drawRect( const t_size &size, const t_pos &pos, const Colour &colour )
{
	irr::video::SColor iColour( colour.getR(), colour.getG(), colour.getB(), colour.getAlpha() );

	mDriver->draw2DRectangle( iColour, irr::core::rect<s32>(
		pos.getX(), pos.getY(), pos.getX() + size.width, pos.getY() + size.height
	) );
}

void
IrrlichtGraphics::drawText( const wchar_t *text, const t_pos &pos, const Colour &colour )
{
	gui::IGUIFont* font = mGui->getBuiltInFont();

	font->draw(
		text,
		core::rect<s32>( pos.getX() , pos.getY(), pos.getX(), pos.getY() ),
		video::SColor( colour.getR(), colour.getG(), colour.getB(), colour.getAlpha() )
	);
}

void
IrrlichtGraphics::setWindowCaption( const std::wstring &caption )
{
	mDevice->setWindowCaption( caption.c_str() );
}

IrrlichtDevice*
IrrlichtGraphics::getDevice() const
{
	return mDevice;
}

IVideoDriver*
IrrlichtGraphics::getDriver() const
{
	return mDriver;
}

ISceneManager*
IrrlichtGraphics::getSceneManager() const
{
	return mSceneManager;
}

IGUIEnvironment*
IrrlichtGraphics::getGui() const
{
	return mGui;
}

