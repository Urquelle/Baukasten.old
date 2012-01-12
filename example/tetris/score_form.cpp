#include "score_form.h"

#include <generic_state.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

#include <sstream>

using namespace Baukasten;

ScoreForm::ScoreForm( const string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) )
{
}

ScoreForm::~ScoreForm()
{
}

void
ScoreForm::render()
{
	irr::video::IVideoDriver *driver = getGraphics()->getDriver();
	gui::IGUIFont* font = getGraphics()->getDevice()->getGUIEnvironment()->getBuiltInFont();

	int x = getPosition().getX();
	int y = getPosition().getY();
	int score = getState<StateInt*>( "state:score" )->getValue();

	std::wstringstream sScore;
	sScore << score;

	// draw score
	font->draw(
		sScore.str().c_str(),
		core::rect<s32>( x , y, x + 40, y + 40 ),
		video::SColor( 127, 127, 127, 255 )
	);
}

