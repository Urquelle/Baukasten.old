#ifndef GRAPHICS_INTERFACE_WNTJGIN0
#define GRAPHICS_INTERFACE_WNTJGIN0

#include "graphics/Global"

namespace Baukasten {

	class IGraphics;

	class BAUKASTEN_EXPORT GraphicsInterface {
	public:
		static IGraphics* instance();

	private:
		GraphicsInterface() {}

		static IGraphics* m_instance;
	};
} /* Baukasten */

#endif /* end of include guard: GRAPHICS_INTERFACE_WNTJGIN0 */
