#ifndef CITY_FORM_VDYKOAZS
#define CITY_FORM_VDYKOAZS

#include "form2d.h"

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

namespace irr {
	namespace gui {
		class IGUIImage;
	} /* scene */
} /* irr */

class CityForm : public Form2d {
public:
	CityForm( const string&, const string&, Baukasten::IGraphics* );
	virtual ~CityForm();

	void render();

private:
	irr::gui::IGUIImage*	mBattleField;
};

#endif /* end of include guard: CITY_FORM_VDYKOAZS */