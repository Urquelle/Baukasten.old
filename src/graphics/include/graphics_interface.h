#ifndef GRAPHICS_INTERFACE_WNTJGIN0
#define GRAPHICS_INTERFACE_WNTJGIN0

namespace Baukasten {
	class Form;
	class IGraphics;

	class GraphicsInterface {
	public:
		static GraphicsInterface* instance();
		virtual ~GraphicsInterface();

		void addCamera();
		void init();
		void renderForm( Form* );

	private:
		GraphicsInterface();

		static GraphicsInterface*	mInstance;
		bool						mInitialised;
		IGraphics*					mImpl;
	};
} /* Baukasten */

#endif /* end of include guard: GRAPHICS_INTERFACE_WNTJGIN0 */
