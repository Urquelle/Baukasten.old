#include "block_form.h"

#include "core/Color"
#include "graphics/IGraphics"
#include "model/GenericState"

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
	auto matrix = state<StateIntVector*>( "state:matrix1" )->values();
	Color cSet( 255, 0, 0, 255 );
	Color cClean( 255, 255, 255, 255 );

	int x = position()[BK_X];
	int x_offset = 0;
	int y = position()[BK_Y];
	int y_offset = 0;
	vec3<float> pos;
	vec2<float> size({ (float)(BLOCK_WIDTH), (float)(BLOCK_HEIGHT) });

	for ( int i = 0; i < 16; ++i ) {
		x_offset = ( i % 4 ) * BLOCK_WIDTH;
		y_offset = (int)( i / 4 ) * BLOCK_HEIGHT;

		pos.set( BK_X, (float)(x + x_offset) );
		pos.set( BK_Y, (float)(y + y_offset) );

		if ( matrix[ i ] == 1 ) {
			graphics()->drawRect( size, pos, cSet );
		}
	}
}
