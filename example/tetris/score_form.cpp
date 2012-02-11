#include "score_form.h"

#include "core/GenericState"
#include "graphics/IGraphics"

#include <sstream>

using namespace Baukasten;

ScoreForm::ScoreForm( const string &id, IGraphics *graphics ) :
	Form( id, graphics )
{
}

ScoreForm::~ScoreForm()
{
}

void
ScoreForm::render()
{
	int score = state<StateInt*>( "state:score" )->value();

	std::wstringstream sScore;
	sScore << score;

	Colour colour( 128, 0, 0, 255 );

	// draw score
	graphics()->drawText( sScore.str().c_str(), position(), colour );
}

