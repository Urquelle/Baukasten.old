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
		void shutDown();

		void drawImage( const string&, const t_size&, const t_pos& );
		void drawLine( const t_pos&, const t_pos&, const Colour& );
		void drawRect( const t_size&, const t_pos&, const Colour& );
		void drawText( const wchar_t*, const t_pos&, const Colour& );

		void setWindowCaption( const std::wstring& );

		IrrlichtDevice* getDevice() const;
		video::IVideoDriver* getDriver() const;
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

