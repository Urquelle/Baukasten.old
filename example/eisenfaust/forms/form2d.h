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

class Form2d : public Baukasten::IrrlichtForm {
public:
	Form2d( const std::string&, const std::string&, Baukasten::IGraphics* );
	virtual ~Form2d();

	void render();

private:
	irr::video::ITexture* 		mBackground;
	irr::video::IVideoDriver*	mDriver;
	irr::scene::ISceneManager*	mSceneManager;
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
