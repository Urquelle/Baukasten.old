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
	Form::render();
}
