#include "worldmap_form.h"

#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
using namespace video;

WorldMapForm::WorldMapForm( const std::string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) ),
	mSceneManager( getGraphics()->getSceneManager() ),
	mDriver( getGraphics()->getDriver() )
{
	mBackground = mDriver->getTexture("media/worldmap.jpg");
}

WorldMapForm::~WorldMapForm()
{
}

void WorldMapForm::render()
{
	mDriver->draw2DImage(
		mBackground, core::position2d<s32>(0,0),
		core::rect<s32>(0,0,1024,768), 0,
		video::SColor(255,255,255,255), true
	);
}

