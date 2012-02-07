#include "field_form.h"

#include "constants.h"

#include <generic_state.h>
#include <igraphics.h>
#include <colour.h>

#include <algorithm>

using namespace Baukasten;

const int FIELD_WIDTH = 12;
const int BLOCK_WIDTH = 4;

FieldForm::FieldForm( const string &id, IGraphics *graphics ) :
	Form( id, graphics )
{
}

FieldForm::~FieldForm()
{
}

void FieldForm::render()
{
	auto matrix = getState<StateIntVector*>( "state:field" )->getValues();
	auto column = getState<StateInt*>( "block:column" )->getValue();
	auto row = getState<StateInt*>( "block:row" )->getValue();

	int i = 0;
	int j = 0;
	auto pos = getPosition();
	v2<float> size({ 40.0, 40.0 });

	Colour cSet( 255, 0, 0, 255 );
	Colour cInMotion( 255, 125, 125, 255 );
	Colour cControl( 255, 125, 125, 125 );

	// draw current column
	getGraphics()->drawRect( { 40.0, 5.0 }, {(float)(240 + column * 40), 10.0, 0.0}, cControl );

	// draw current row
	getGraphics()->drawRect( { 5.0, 40.0 }, {230.0, (float)(20 + row * 40), 0.0}, cControl );

	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, size, this, &cSet, &cControl, &cInMotion]( int k ) {
		float x = pos.getX() + 40 * ( i % FIELD_WIDTH );
		float y = pos.getY() + 40 * j;

		auto graphics = this->getGraphics();

		// draw already occupied blocks
		if ( SET == k ) {
			graphics->drawRect( size, {x, y, 0.0}, cSet );
			graphics->drawText( L"1", {x + 20, y + 20, 0.0}, cControl );
		}

		// draw falling blocks
		if ( IN_MOTION == k ) {
			graphics->drawRect( size, {x, y, 0.0}, cInMotion );
			graphics->drawText( L"2", {x + 20, y + 20, 0.0}, cControl );
		}

		if ( CLEAN == k ) {
			graphics->drawText( L"0", {x + 20, y + 20, 0.0}, cControl );
		}

		// draw + on the field
		if ( ( i % FIELD_WIDTH ) < FIELD_WIDTH - 1 && ( i / FIELD_WIDTH ) < 17 ) {
			graphics->drawPoint( { x + 40, y + 40, 0.0 }, 2, cSet );
		}

		++i;
		j += ( ( i > 0 ) && ( i % FIELD_WIDTH ) == 0 ) ? 1 : 0;
	});
}

