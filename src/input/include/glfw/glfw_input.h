#ifndef GLFW_INPUT_H_XWQRTCFU
#define GLFW_INPUT_H_XWQRTCFU

#include "input/Global"
#include "input/IInput"

namespace Baukasten {
	class Services;

	/*!
	 * \brief class implementing the IInput interface.
	 * \ingroup services input
	 * \headerfile InputImpl "audio/AudioImpl"
	 *
	 * using the GLFW library, this class implements the IInput interface
	 * providing all the basic methods to react to user input.
	 *
	 * \note the implementation classes are not supposed to be used directly. use
	 * the according method to retrieve the input interface in the Services class.
	 *
	 * \sa InputInterface::instance()
	 * \sa Services::inputService()
	 */
	class BAUKASTEN_EXPORT GlfwInput : public IInput {
	public:

		/*! constructor. */
		GlfwInput();

		/*! destructor. */
		virtual ~GlfwInput();

		/*! \sa IInput::init() */
		void      init( Services& );

		/*! \sa IInput::keyState() */
		KeyState  keyState( const Key ) const;

		/*! \sa IInput::process() */
		void      process() const;

		/*! \sa IInput::shutdown() */
		void      shutdown();
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_INPUT_H_XWQRTCFU */

