#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "input/Global"
#include "input/InputInterface"
#include "services/IService"

namespace Baukasten {

	class IInputPrivate;
	class Services;

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup input
	 * @{
	 *
	 * \class IInput
	 * \brief input module interface.
	 * \headerfile IInput "input/IInput"
	 *
	 * defines methods which an implementation class has to
	 * provide in order to be used as Input Service.
	 */
	class BAUKASTEN_EXPORT IInput : public IService {
	public:

		/*!
		 * \brief constructor.
		 *
		 * basic constructor of the class.
		 *
		 * \param name name of the service.
		 */
		IInput( const string& );

		/*!
		 * \brief process user inputs.
		 *
		 * goes through the list of currently occured user inputs and
		 * emits the appropriate signals for every event.
		 */
		virtual void process() const = 0;

		/*!
		 * \brief query the key state.
		 *
		 * query for the state of the given key.
		 *
		 * \param key key to which the state will be returned.
		 * \return KeyState value.
		 */
		virtual KeyState keyState( const Key key ) const = 0;

		/*!
		 * \brief get the KeyEvent pointer to onKeyDown signal.
		 *
		 * in order for you to be able to react to user input, you have
		 * to register a method to be called on the onKeyDown event.
		 *
		 * \return the signal object for the onKeyDown event.
		 */
		KeyEvent* onKeyDown();

		/*!
		 * \brief get the KeyEvent pointer to onKeyUp signal.
		 *
		 * in order for others to be able to react to user input, you have
		 * to register a method to be called on the onKeyUp event.
		 *
		 * \return the signal object for the onKeyUp event.
		 */
		KeyEvent* onKeyUp();

	private:
		BK_IMPL_PTR( IInput );
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
