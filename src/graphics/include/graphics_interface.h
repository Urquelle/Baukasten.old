#ifndef GRAPHICS_INTERFACE_WNTJGIN0
#define GRAPHICS_INTERFACE_WNTJGIN0

namespace Baukasten {
	class Form;

	class GraphicsInterface {
	public:
		static GraphicsInterface* instance();
		virtual ~GraphicsInterface();

		void renderForm( Form* );
		void addCamera();

	private:
		GraphicsInterface();

		static GraphicsInterface* mInstance;
	};
} /* Baukasten */

#endif /* end of include guard: GRAPHICS_INTERFACE_WNTJGIN0 */
