#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "core/IServiceInterface"
#include "input/Global"
#include "input/InputInterface"

namespace Baukasten {

	class CoreServices;
	class IInputPrivate;

	class BAUKASTEN_EXPORT IInput : public IServiceInterface {
	public:
		IInput( const string& );

		virtual void process() const = 0;
		virtual void shutdown() {}

		virtual KeyState keyState( const Key ) const = 0;

		KeyEvent* onKeyDown();
		KeyEvent* onKeyUp();

	private:
		BK_PIMPL_PTR( IInput );
	};
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
