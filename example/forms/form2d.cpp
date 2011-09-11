#include "form2d.h"

#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
using namespace video;

Form2d::Form2d( const std::string &id, const std::string &fileName, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) ),
	mSceneManager( getGraphics()->getSceneManager() ),
	mDriver( getGraphics()->getDriver() )
{
	mBackground = mDriver->getTexture( fileName.c_str() );
}

Form2d::~Form2d()
{
}

void Form2d::render()
{
	mDriver->draw2DImage(
		mBackground, core::position2d<s32>(0,0),
		core::rect<s32>(0,0,1024,768), 0,
		video::SColor(255,255,255,255), true
	);
}

