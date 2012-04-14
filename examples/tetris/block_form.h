#ifndef BLOCK_FORM_21IENA7S
#define BLOCK_FORM_21IENA7S

#include "core/Color"
#include "graphics/IGraphics"
#include "model/Form"
#include "model/GenericState"

#include "constants.h"

using namespace Baukasten;

class BlockForm : public Form {
public:
	BlockForm( const std::string &id ) :
        Form( id )
    {
    }

	virtual ~BlockForm()
    {
    }

	virtual void render()
    {
        auto matrix = state<StateIntVector*>( "state:matrix" )->values();

        Color cSet( Color::BK_RED );
        Color cClean( Color::BK_WHITE );

        int x = position()[BK_X];
        int x_offset = 0;
        int y = position()[BK_Y];
        int y_offset = 0;
        vec3<float> pos;
        vec2<float> size({ (float)(BLOCK_PX_WIDTH), (float)(BLOCK_PX_HEIGHT) });

        for ( int i = 0; i < BLOCK_SIZE; ++i ) {
            x_offset = ( i % BLOCK_WIDTH ) * BLOCK_PX_WIDTH;
            y_offset = (int)( i / BLOCK_HEIGHT ) * BLOCK_PX_HEIGHT;

            pos.set( BK_X, (float)(x + x_offset) );
            pos.set( BK_Y, (float)(y + y_offset) );

            if ( matrix[ i ] == SET ) {
                graphics().drawRect( size, pos, cSet );
            } else if ( matrix[ i ] == CLEAN ) {
                graphics().drawRect( size, pos, cClean );
            }
        }
    }
};

#endif /* end of include guard: BLOCK_FORM_21IENA7S */
