#ifndef GRAPHICS_INTERFACE_WNTJGIN0
#define GRAPHICS_INTERFACE_WNTJGIN0

#include "graphics/Global"

namespace Baukasten {

	class IGraphics;

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup graphics
	 * @{
	 *
	 * \class GraphicsInterface
	 * \brief graphics interface class.
	 * \headerfile GraphicsInterface "graphics/GraphicsInterface"
	 *
	 * the class provides the interface to retrieve an object
	 * implementing the IGraphics interface.
	 */
	class BAUKASTEN_EXPORT GraphicsInterface {
	public:

		/*!
		 * \brief singleton method to retrieve implementation.
		 *
		 * singleton method which provides the interface to retrieve
		 * the object implementing the IGraphics interface.
		 *
		 * \return pointer to an IGraphics object.
		 */
		static IGraphics* instance();

	private:
		GraphicsInterface() {}

		static IGraphics* m_instance;
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: GRAPHICS_INTERFACE_WNTJGIN0 */
