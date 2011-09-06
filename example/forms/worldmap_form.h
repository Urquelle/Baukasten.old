#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include <irrlicht/irrlicht_form.h>

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

class WorldMapForm : public Baukasten::IrrlichtForm {
public:
	WorldMapForm( const std::string&, Baukasten::IGraphics* );
	virtual ~WorldMapForm();
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
