#include "block_form.h"

#include <colour.h>
#include <generic_state.h>
#include <igraphics.h>

using namespace Baukasten;

BlockForm::BlockForm( const string &id, IGraphics *graphics ) :
	Form( id, graphics ),
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
	auto matrix = getState<StateIntVector*>( "state:matrix1" )->getValues();
	Colour cSet( 255, 0, 0, 255 );
	Colour cClean( 255, 255, 255, 255 );

	int x = getPosition().getX();
	int x_offset = 0;
	int y = getPosition().getY();
	int y_offset = 0;
	t_pos pos;
	t_size size({ (float)(BLOCK_WIDTH), (float)(BLOCK_HEIGHT) });

	for ( int i = 0; i < 16; ++i ) {
		x_offset = ( i % 4 ) * BLOCK_WIDTH;
		y_offset = (int)( i / 4 ) * BLOCK_HEIGHT;

		pos.setX((float)(x + x_offset));
		pos.setY((float)(y + y_offset));

		if ( matrix[ i ] == 1 ) {
			getGraphics()->drawRect( size, pos, cSet );
		} else {
			getGraphics()->drawRect( size, pos, cClean );
		}
	}
}
