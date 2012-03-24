#include "score_form.h"

#include "graphics/Font"
#include "graphics/IGraphics"
#include "model/GenericState"

#include <sstream>

using namespace Baukasten;

ScoreForm::ScoreForm( const string &id, IGraphics *graphics ) :
	Form( id, graphics ),
	m_font( new Font( "/usr/share/fonts/corefonts/arial.ttf", 20 ) )
{
}

ScoreForm::~ScoreForm()
{
}

void
ScoreForm::render()
{
	int score = state<StateInt*>( "state:score" )->value();

	std::stringstream sScore;
	sScore << "Your Score: " << score;

	Color color( 128, 0, 0, 255 );

	// draw score
	graphics()->drawText( m_font, sScore.str(), position(), color );
}

