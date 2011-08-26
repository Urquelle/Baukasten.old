#ifndef GRAPHICS_INTERFACE_WNTJGIN0
#define GRAPHICS_INTERFACE_WNTJGIN0

namespace Baukasten {
	class Form;
	class IGraphics;

	class GraphicsInterface {
	public:
		static IGraphics* instance();
		virtual ~GraphicsInterface() {}

	private:
		GraphicsInterface() {}

		static IGraphics* mInstance;
	};
} /* Baukasten */

#endif /* end of include guard: GRAPHICS_INTERFACE_WNTJGIN0 */
