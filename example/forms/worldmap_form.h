#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include <irrlicht/irrlicht_form.h>

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

namespace irr {
	namespace scene {
		class ISceneManager;
	} /* scene */
	namespace video {
		class IVideoDriver;
		class ITexture;
	} /* video */
} /* irr */

class WorldMapForm : public Baukasten::IrrlichtForm {
public:
	WorldMapForm( const std::string&, Baukasten::IGraphics* );
	virtual ~WorldMapForm();

	void render();

private:
	irr::video::ITexture* 		mBackground;
	irr::video::IVideoDriver*	mDriver;
	irr::scene::ISceneManager*	mSceneManager;
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
