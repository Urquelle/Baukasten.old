#include "field_form.h"

#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

#include <algorithm>

using namespace Baukasten;

FieldForm::FieldForm( const string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) )
{
}

FieldForm::~FieldForm()
{
}

void FieldForm::render()
{
	irr::video::IVideoDriver *driver = getGraphics()->getDriver();
	auto matrix = getState<StateIntVector*>( "state:field" )->getValues();

	int i = 0;
	int j = 0;
	auto pos = getPosition();
	t_size size = getSize();

	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, &size, driver, this]( int k ) {
		int x = pos.getX() + 40 * ( i % 12 );
		int y = pos.getY() + 40 * j;

		driver->draw2DRectangle(
			irr::video::SColor( 255, 125, 125, 100 ),
			irr::core::rect<s32>(
				x, y, x + 40, y + 40
			)
		);

		++i;
		j += ( ( i > 11 ) && ( i % 12 ) == 0 ) ? 1 : 0;
	});
}

