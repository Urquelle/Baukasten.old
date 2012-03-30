#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "input/Global"
#include "input/InputInterface"
#include "services/IService"

namespace Baukasten {

	class IInputPrivate;
	class Services;

	class BAUKASTEN_EXPORT IInput : public IService {
	public:
		IInput( const string& );

		virtual void process() const = 0;

		virtual KeyState keyState( const Key ) const = 0;

		KeyEvent* onKeyDown();
		KeyEvent* onKeyUp();

	private:
		BK_PIMPL_PTR( IInput );
	};
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
