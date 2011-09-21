#ifndef CITY_FORM_VDYKOAZS
#define CITY_FORM_VDYKOAZS

#include "form2d.h"

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

class CityForm : public Form2d {
public:
	CityForm( const string&, Baukasten::IGraphics* );
	virtual ~CityForm();

	void render();
};

#endif /* end of include guard: CITY_FORM_VDYKOAZS */
