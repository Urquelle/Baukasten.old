#include "field_form.h"

#include "constants.h"

#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

#include <algorithm>

using namespace Baukasten;

const int FIELD_WIDTH = 12;
const int BLOCK_WIDTH = 4;

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
	gui::IGUIFont* font = getGraphics()->getDevice()->getGUIEnvironment()->getBuiltInFont();

	auto matrix = getState<StateIntVector*>( "state:field" )->getValues();
	auto column = getState<StateInt*>( "block:column" )->getValue();
	auto row = getState<StateInt*>( "block:row" )->getValue();

	int i = 0;
	int j = 0;
	auto pos = getPosition();
	t_size size = getSize();

	irr::video::SColor cSet( 255, 0, 0, 255 );
	irr::video::SColor cInMotion( 255, 125, 125, 255 );
	irr::video::SColor cControl( 255, 125, 125, 125 );

	// draw current column
	driver->draw2DRectangle(
		cControl, irr::core::rect<s32>( 240 + column * 40, 10, 240 + column * 40 + 40, 15 )
	);

	// draw current row
	driver->draw2DRectangle(
		cControl, irr::core::rect<s32>( 230, 20 + row * 40, 235, 20 + 40 + row * 40 )
	);

	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, driver, this, &cSet, &cInMotion, font]( int k ) {
		int x = pos.getX() + 40 * ( i % FIELD_WIDTH );
		int y = pos.getY() + 40 * j;

		// draw already occupied blocks
		if ( SET == k ) {
			driver->draw2DRectangle(
				cSet, irr::core::rect<s32>( x, y, x + 40, y + 40 )
			);
		}

		if ( IN_MOTION == k ) {
			driver->draw2DRectangle(
				cInMotion, irr::core::rect<s32>( x, y, x + 40, y + 40 )
			);
		}

		// draw debug information
		font->draw( ( k == SET ) ? L"1" : ( ( k == IN_MOTION ) ? L"2" : L"0" ),
			core::rect<s32>( x , y, x + 40, y + 40 ),
			video::SColor( 127, 127, 127, 255 )
		);

		++i;
		j += ( ( i > 0 ) && ( i % FIELD_WIDTH ) == 0 ) ? 1 : 0;
	});
}

