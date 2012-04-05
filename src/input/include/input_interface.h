#ifndef INPUTINTERFACE_AKBKP72C
#define INPUTINTERFACE_AKBKP72C

#include "input/Global"

namespace Baukasten {
	class IInput;

	/*!
	 * \brief input interface class.
	 * \ingroup services input interface
	 * \headerfile InputInterface "input/InputInterface"
	 *
	 * the class provides the interface to retrieve an object
	 * implementing the IInput interface.
	 */
	class BAUKASTEN_EXPORT InputInterface {
	public:

		/*!
		 * \brief singleton method to retrieve implementation.
		 *
		 * singleton method which provides the interface to retrieve
		 * the object implementing the IInput interface.
		 *
		 * \return pointer to an IInput object.
		 */
		static IInput* instance();

	private:
		InputInterface();

		static IInput* m_instance;
	};
} /* Baukasten */

#endif /* end of include guard: INPUTINTERFACE_AKBKP72C */
