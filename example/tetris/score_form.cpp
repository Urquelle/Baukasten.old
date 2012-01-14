#include "score_form.h"

#include <generic_state.h>
#include <igraphics.h>

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
	float x = getPosition().getX();
	float y = getPosition().getY();
	int score = getState<StateInt*>( "state:score" )->getValue();

	std::wstringstream sScore;
	sScore << score;

	Colour colour( 128, 0, 0, 255 );

	// draw score
	getGraphics()->drawText( sScore.str().c_str(), { x, y, 0.0 }, colour );
}

