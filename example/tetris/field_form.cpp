#include "field_form.h"

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
	auto matrix = getState<StateIntVector*>( "state:field" )->getValues();
	auto block = getState<StateIntVector*>( "block:current" )->getValues();
	auto column = getState<StateInt*>( "block:column" )->getValue();
	auto row = getState<StateInt*>( "block:row" )->getValue();
	auto step = getState<StateInt*>( "state:step" )->getValue();

	int i = 0;
	int j = 0;
	auto pos = getPosition();
	t_size size = getSize();

	irr::video::SColor cSet( 255, 0, 0, 0 );
	irr::video::SColor cBlock( 255, 125, 125, 0 );
	irr::video::SColor cControl( 255, 125, 125, 125 );

	driver->draw2DRectangle(
		irr::video::SColor( 255, 100, 30, 50 ), irr::core::rect<s32>( 240 + column * 40, 10, 240 + column * 40 + 40, 15 )
	);

	// draw current row
	driver->draw2DRectangle(
		cControl, irr::core::rect<s32>( 230, 20 + row * 40, 235, 20 + 40 + row * 40 )
	);

	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, &row, &column, &block, driver, this, &cSet, &cBlock, &step]( int k ) {
		int x = pos.getX() + 40 * ( i % FIELD_WIDTH );
		int y = pos.getY() + 40 * j;

		// draw already occupied blocks
		if ( k ) {
			driver->draw2DRectangle(
				cSet, irr::core::rect<s32>( x, y, x + 40, y + 40 )
			);
		}

		// draw current block
		int startBlock = ( row * FIELD_WIDTH ) + ( column - 1 );
		int endBlock = ( ( row + 3 ) * FIELD_WIDTH ) + ( column + 2 );
		int range = ( i - column + 1 ) % FIELD_WIDTH;
		if ( block.size() && i >= startBlock && i <= endBlock && range >= 0 && range < BLOCK_WIDTH ) {
			int index = ( i - row * FIELD_WIDTH - column + 1 ) - ( FIELD_WIDTH - BLOCK_WIDTH ) * ( j - row );
			if ( index > 0 && index < 15 && block[ index ] ) {
				driver->draw2DRectangle(
					cBlock, irr::core::rect<s32>( x, y + row, x + 40, y + 40 + row )
				);
			}
		}

		++i;
		j += ( ( i > 0 ) && ( i % FIELD_WIDTH ) == 0 ) ? 1 : 0;
	});
}

