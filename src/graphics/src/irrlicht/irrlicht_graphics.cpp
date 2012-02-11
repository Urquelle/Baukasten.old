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

	mDriver			= mDevice->videoDriver();
	mSceneManager	= mDevice->sceneManager();
	mGui			= mDevice->gUIEnvironment();

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
IrrlichtGraphics::shutdown()
{
	mDevice->drop();
}

void
IrrlichtGraphics::drawImage( const std::string &filePath, const v2<float> &size, const v3<float> &pos )
{
	irr::video::ITexture* mBackground = mDriver->texture( filePath.c_str() );
	mDriver->draw2DImage(
		mBackground,
		core::position2d<s32>( pos.x(), pos.y() ),
		core::rect<s32>( 0, 0, size.x(), size.y() ),
		0, video::SColor(255,255,255,255), true
	);
}

void
IrrlichtGraphics::drawLine( const v3<float> &from, const v3<float> &to, const Colour &colour )
{
	irr::video::SColor iColour( colour.r(), colour.g(), colour.b(), colour.alpha() );

	mDriver->draw2DLine(
		irr::core::position2d<s32>( from.x(), from.y() ),
		irr::core::position2d<s32>( to.x(), to.y() ),
		iColour
	);
}

void
IrrlichtGraphics::drawRect( const v2<float> &size, const v3<float> &pos, const Colour &colour )
{
	irr::video::SColor iColour( colour.r(), colour.g(), colour.b(), colour.alpha() );

	mDriver->draw2DRectangle( iColour, irr::core::rect<s32>(
		pos.x(), pos.y(), pos.x() + size.x(), pos.y() + size.y()
	) );
}

void
IrrlichtGraphics::drawText( const wchar_t *text, const v3<float> &pos, const Colour &colour )
{
	gui::IGUIFont* font = mGui->builtInFont();

	font->draw(
		text,
		core::rect<s32>( pos.x() , pos.y(), pos.x(), pos.y() ),
		video::SColor( colour.r(), colour.g(), colour.b(), colour.alpha() )
	);
}

void
IrrlichtGraphics::setWindowCaption( const std::wstring &caption )
{
	mDevice->setWindowCaption( caption.c_str() );
}

IrrlichtDevice*
IrrlichtGraphics::device() const
{
	return mDevice;
}

IVideoDriver*
IrrlichtGraphics::driver() const
{
	return mDriver;
}

ISceneManager*
IrrlichtGraphics::sceneManager() const
{
	return mSceneManager;
}

IGUIEnvironment*
IrrlichtGraphics::gui() const
{
	return mGui;
}

