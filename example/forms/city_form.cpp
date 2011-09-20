#include "city_form.h"

#include <debug.h>
#include <irrlicht/irrlicht_graphics.h>

using namespace Baukasten;

CityForm::CityForm( const string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) )
{
}

CityForm::~CityForm()
{
}

void CityForm::render()
{
	BK_DEBUG( getId() + " render()" );
}

