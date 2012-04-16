#include "field_form.h"

#include "constants.h"

#include "core/Color"
#include "graphics/Font"
#include "graphics/IGraphics"
#include "model/GenericState"

#include <algorithm>

using namespace Baukasten;

FieldForm::FieldForm( const string &id ) :
	Form( id ),
	m_font( new Font( "/usr/share/fonts/corefonts/arial.ttf", 10 ) )
{
}

FieldForm::~FieldForm()
{
}

void FieldForm::render()
{
	auto matrix = state<StateIntVector*>( "state:field" )->values();
	auto column = state<StateInt*>( "block:column" )->value();
	auto row = state<StateInt*>( "block:row" )->value();

	int i = 0;
	int j = 0;
	auto pos = position();
	Vector2 size({ 40.0, 40.0 });

	Color cSet( 255, 0, 0, 255 );
	Color cInMotion( 255, 125, 125, 255 );
	Color cControl( 255, 125, 125, 125 );

	// draw current column
	graphics().drawRect( { 40.0, 5.0 }, {(float)(240 + column * 40), 10.0, 0.0}, cControl );

	// draw current row
	graphics().drawRect( { 5.0, 40.0 }, {230.0, (float)(20 + row * 40), 0.0}, cControl );

	for_each( matrix.begin(), matrix.end(), [&i, &j, &pos, size, this, &cSet, &cControl, &cInMotion]( int k ) {
		float x = pos[BK_X] + 40 * ( i % FIELD_WIDTH );
		float y = pos[BK_Y] + 40 * j;

		auto &graphics = this->graphics();

		// draw already occupied blocks
		if ( SET == k ) {
			graphics.drawRect( size, {x, y, 0.0}, cSet );
			graphics.drawText( m_font, "1", {x + 20, y + 20, 0.0}, cControl );
		}

		// draw falling blocks
		if ( IN_MOTION == k ) {
			graphics.drawRect( size, {x, y, 0.0}, cInMotion );
			graphics.drawText( m_font, "2", {x + 20, y + 20, 0.0}, Color( 0, 0, 0, 255 ) );
		}

		if ( CLEAN == k ) {
			graphics.drawText( m_font, "0", {x + 20, y + 20, 0.0}, cControl );
		}

		// draw + on the field
		if ( ( i % FIELD_WIDTH ) < FIELD_WIDTH - 1 && ( i / FIELD_WIDTH ) < 17 ) {
			graphics.drawPoint( { x + 40, y + 40, 0.0 }, 2, cSet );
		}

		++i;
		j += ( ( i > 0 ) && ( i % FIELD_WIDTH ) == 0 ) ? 1 : 0;
	});
}

