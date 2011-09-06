#include "worldmap_form.h"

#include <irrlicht/irrlicht_graphics.h>

using namespace Baukasten;

WorldMapForm::WorldMapForm( const std::string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) )
{
}

WorldMapForm::~WorldMapForm()
{
}

