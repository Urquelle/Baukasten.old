#ifndef WORLD_MAP_FORM_EVZ408FS
#define WORLD_MAP_FORM_EVZ408FS

#include "ogre_form.h"

namespace Ogre {
	class Entity;
} /* Ogre */

class WorldMapForm : public OgreForm {
public:
	WorldMapForm( const std::string& );
	virtual ~WorldMapForm();

	void render();

private:
	Ogre::Entity*	mGround;
};

#endif /* end of include guard: WORLD_MAP_FORM_EVZ408FS */
