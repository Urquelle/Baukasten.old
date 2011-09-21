#include "city_form.h"

#include <debug.h>
#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

using namespace Baukasten;

CityForm::CityForm( const string &id, IGraphics *graphics ) :
	Form2d(
		id,
		"media/images/1024x768/city.png",
		dynamic_cast<IrrlichtGraphics*>( graphics )
	)
{
	addState( "state:mode", new StateInt( "state:mode", 0 ) );
	setSize( { 20, 20 } );
}

CityForm::~CityForm()
{
}

void CityForm::render()
{
	Form2d::render();
}

