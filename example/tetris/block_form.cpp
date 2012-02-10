#include "block_form.h"

#include "core/Colour"
#include "core/GenericState"
#include "graphics/IGraphics"

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

	int x = getPosition()[BK_X];
	int x_offset = 0;
	int y = getPosition()[BK_Y];
	int y_offset = 0;
	vec3<float> pos;
	vec2<float> size({ (float)(BLOCK_WIDTH), (float)(BLOCK_HEIGHT) });

	for ( int i = 0; i < 16; ++i ) {
		x_offset = ( i % 4 ) * BLOCK_WIDTH;
		y_offset = (int)( i / 4 ) * BLOCK_HEIGHT;

		pos.set( BK_X, (float)(x + x_offset) );
		pos.set( BK_Y, (float)(y + y_offset) );

		if ( matrix[ i ] == 1 ) {
			getGraphics()->drawRect( size, pos, cSet );
		}
	}
}
