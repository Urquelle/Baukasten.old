#include "block_form.h"

#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

#include <algorithm>
#include <sstream>

using namespace Baukasten;

BlockForm::BlockForm( const string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) ),
	BLOCK_WIDTH( 40 ),
	BLOCK_HEIGHT( 40 )
{
}

BlockForm::~BlockForm()
{
}

void
BlockForm::render()
{
	irr::video::IVideoDriver *driver = getGraphics()->getDriver();
	auto matrix = getState<StateIntVector*>( "state:matrix1" )->getValues();
	irr::video::SColor cSet( 255, 0, 0, 255 );
	irr::video::SColor cClean( 255, 255, 255, 255 );

	int x = getPosition().getX();
	int x_offset = 0;
	int y = getPosition().getY();
	int y_offset = 0;

	for ( int i = 0; i < 16; ++i ) {
		x_offset = ( i % 4 ) * BLOCK_WIDTH;
		y_offset = (int)( i / 4 ) * BLOCK_HEIGHT;

		if ( matrix[ i ] == 1 ) {
			driver->draw2DRectangle( cSet, irr::core::rect<s32>(
				x + x_offset, y + y_offset, x + x_offset + BLOCK_WIDTH, y + y_offset + BLOCK_HEIGHT
			) );
		} else {
			driver->draw2DRectangle( cClean, irr::core::rect<s32>(
				x + x_offset, y + y_offset, x + x_offset + BLOCK_WIDTH, y + y_offset + BLOCK_HEIGHT
			) );
		}
	}
}
