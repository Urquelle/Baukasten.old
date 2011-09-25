#include "city_form.h"

#include "../global.h"

#include <debug.h>
#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

CityForm::CityForm( const string &id, const string &filePath, IGraphics *graphics ) :
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
	int mode = getState<StateInt*>( "state:mode" )->getValue();
	switch ( mode ) {
	case Mode::MODE_WORLDMAP:
		Form2d::render();
		break;
	case Mode::MODE_RUNSCENE:
		BK_DEBUG( "render battle scene" );
		break;
	}
}

