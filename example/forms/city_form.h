#ifndef CITY_FORM_VDYKOAZS
#define CITY_FORM_VDYKOAZS

#include <irrlicht/irrlicht_form.h>

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

class CityForm : public Baukasten::IrrlichtForm {
public:
	CityForm( const string&, Baukasten::IGraphics* );
	virtual ~CityForm();

	void render();
};

#endif /* end of include guard: CITY_FORM_VDYKOAZS */
