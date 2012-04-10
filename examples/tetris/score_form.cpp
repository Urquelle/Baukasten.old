#include "score_form.h"

#include "graphics/Font"
#include "graphics/IGraphics"
#include "model/GenericState"

#include <sstream>

using namespace Baukasten;

ScoreForm::ScoreForm( const string &id ) :
	Form( id ),
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

	// draw score
	graphics().drawText( m_font, sScore.str(), position(), Color( Color::BK_GREEN ) );
}

