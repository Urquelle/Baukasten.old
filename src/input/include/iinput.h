#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "input/Global"
#include "input/InputInterface"

namespace Baukasten {

	class CoreServices;
	class IInputPrivate;

	class BAUKASTEN_EXPORT IInput {
	public:
		IInput();
		virtual bool init( CoreServices* ) = 0;
		virtual void process() const = 0;
		virtual void shutdown() {}
		virtual string serviceName() const = 0;

		KeyEvent* onKeyDown();
		KeyEvent* onKeyUp();

		bool isInitialised() const;

	protected:
		void setInitialised( bool );

	private:
		BK_PIMPL_PTR( IInput );
	};
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
