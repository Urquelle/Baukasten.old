#ifndef INFO_FORM_H_6COJRM2B
#define INFO_FORM_H_6COJRM2B

#include "graphics/Font"
#include "graphics/IGraphics"
#include "model/Form"

using namespace Baukasten;

class InfoForm : public Form {
public:
	InfoForm( const string &id ) :
		Form( id ),
		m_font( new Font( "/usr/share/fonts/corefonts/georgia.ttf", 15 ) )
	{
	}

	virtual ~InfoForm()
	{
		delete m_font;
	}

	virtual void render()
	{
		graphics().drawRect( size(), position(), Color::BK_WHITE );

		graphics().drawText(
			m_font, "q to Quit",
			position() + Vector3{ 5, 15, 0 },
			Color::BK_BLACK );

		graphics().drawText(
			m_font, "right arrow to move right",
			position() + Vector3{ 5, 30, 0 },
			Color::BK_BLACK );

		graphics().drawText(
			m_font, "left arrow to move left",
			position() + Vector3{ 5, 45, 0 },
			Color::BK_BLACK );

		graphics().drawText(
			m_font, "up arrow to rotate",
			position() + Vector3{ 5, 60, 0 },
			Color::BK_BLACK );
	}

private:
	Font* m_font;
};

#endif /* end of include guard: INFO_FORM_H_6COJRM2B */

