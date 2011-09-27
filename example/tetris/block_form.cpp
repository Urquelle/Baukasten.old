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

void BlockForm::render()
{
	irr::video::IVideoDriver *driver = getGraphics()->getDriver();
	auto pos = getPosition();

	std::stringstream s;
	s << "state:matrix" << getState<StateInt*>( "state:currentMatrix" )->getValue();

	int i = 0;
	int j = 0;
	auto matrix = getState<StateIntVector*>( s.str() )->getValues();
	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, driver, this]( int k ) {
		int x = pos.getX() + BLOCK_WIDTH * ( i % 4 );
		int y = pos.getY() + BLOCK_HEIGHT * j;

		if ( k ) {
			driver->draw2DRectangle(
				irr::video::SColor(),
				irr::core::rect<s32>( x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT )
			);
		}

		++i;
		j += ( ( i > 4 ) && ( i % 4 ) == 0 ) ? 1 : 0;
	});
	Form::render();
}
