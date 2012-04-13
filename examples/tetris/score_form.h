#ifndef SCORE_FORM_H_MPIAXVNA
#define SCORE_FORM_H_MPIAXVNA

#include "model/Form"
#include "model/Global"

#include "graphics/Font"
#include "graphics/IGraphics"
#include "model/GenericState"

#include <sstream>

using namespace Baukasten;

class ScoreForm : public Form {
public:
	ScoreForm( const string &id ) :
        Form( id ),
        m_font( new Font( "/usr/share/fonts/corefonts/arial.ttf", 20 ) )
    {
    }

	virtual ~ScoreForm()
    {
    }

	void render()
    {
        int score = state<StateInt*>( "state:score" )->value();

        stringstream sScore;
        sScore << "Your Score: " << score;

        // draw score
        graphics().drawText( m_font, sScore.str(), position(), Color( Color::BK_GREEN ) );
    }

private:
	Baukasten::IFont* m_font;
};

#endif /* end of include guard: SCORE_FORM_H_MPIAXVNA */

