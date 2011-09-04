#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include <ogre/ogre_form.h>

namespace Baukasten {
	class OgreInterface;
} /* Baukasten */

class WorldMapForm : public Baukasten::OgreForm {
public:
	WorldMapForm( const std::string&, Baukasten::OgreInterface* );
	virtual ~WorldMapForm();
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
