#ifndef IRRLICHT_GRAPHICS_NAW2JQDS
#define IRRLICHT_GRAPHICS_NAW2JQDS

#include "global.h"

#include "igraphics.h"

namespace irr {
	class IrrlichtDevice;

	namespace scene {
		class ISceneManager;
	} /* scene */

	namespace gui {
		class IGUIEnvironment;
	} /* gui */

	namespace video {
		class IVideoDriver;
	} /* video */
} /* irr */

namespace Baukasten {

	using namespace irr;

	class BAUKASTEN_EXPORT IrrlichtGraphics :
		public IGraphics {
	public:
		IrrlichtGraphics();
		virtual ~IrrlichtGraphics();

		int init();
		void render();
		void shutDown();

		scene::ISceneManager* getSceneManager() const;
		gui::IGUIEnvironment* getGui() const;

	private:
		IrrlichtDevice* 		mDevice;
		video::IVideoDriver*	mDriver;
		scene::ISceneManager*	mSceneManager;
		gui::IGUIEnvironment*	mGui;
	};
} /* Baukasten */

#endif /* end of include guard: IRRLICHT_GRAPHICS_NAW2JQDS */

