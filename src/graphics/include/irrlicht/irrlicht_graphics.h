#ifndef IRRLICHT_GRAPHICS_NAW2JQDS
#define IRRLICHT_GRAPHICS_NAW2JQDS

#include "global.h"

#include "igraphics.h"

#include "colour.h"

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

	class CoreServices;
	class Form;

	class BAUKASTEN_EXPORT IrrlichtGraphics :
		public IGraphics {
	public:
		IrrlichtGraphics();
		virtual ~IrrlichtGraphics();

		int init( CoreServices* );
		void render( Form* );
		void shutdown();

		void drawImage( const string&, const v2<float>&, const v3<float>& );
		void drawLine( const v3<float>&, const v3<float>&, const Colour& );
		void drawRect( const v2<float>&, const v3<float>&, const Colour& );
		void drawText( const wchar_t*, const v3<float>&, const Colour& );

		void setWindowCaption( const std::wstring& );
		string serviceName() const { return "Irrlicht"; }

		IrrlichtDevice* device() const;
		video::IVideoDriver* driver() const;
		scene::ISceneManager* sceneManager() const;
		gui::IGUIEnvironment* gui() const;

	private:
		IrrlichtDevice* 		mDevice;
		video::IVideoDriver*	mDriver;
		scene::ISceneManager*	mSceneManager;
		gui::IGUIEnvironment*	mGui;
	};
} /* Baukasten */

#endif /* end of include guard: IRRLICHT_GRAPHICS_NAW2JQDS */

