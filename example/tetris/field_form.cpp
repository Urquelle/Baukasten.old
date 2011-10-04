#include "field_form.h"

#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

#include <algorithm>

using namespace Baukasten;

const int FIELD_WIDTH = 13;
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

	int i = 0;
	int j = 0;
	auto pos = getPosition();
	t_size size = getSize();

	irr::video::SColor cSet( 255, 0, 0, 0 );
	irr::video::SColor cBlock( 255, 125, 125, 0 );

	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, &row, &column, &block, driver, this, &cSet, &cBlock]( int k ) {
		int x = pos.getX() + 40 * ( i % 13 );
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
			int index = ( i - column + 1 ) - ( FIELD_WIDTH - BLOCK_WIDTH ) * ( j - row );
			if ( block[ index ] ) {
				driver->draw2DRectangle(
					cBlock, irr::core::rect<s32>( x, y, x + 40, y + 40 )
				);
			}
		}

		++i;
		j += ( ( i > 0 ) && ( i % 13 ) == 0 ) ? 1 : 0;
	});
}

