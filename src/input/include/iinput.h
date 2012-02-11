#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "model/Global"

#include "input/InputInterface"

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT IInput {
	public:
		IInput() : mInitialised( false ) {}
		virtual bool init( CoreServices* ) = 0;
		virtual void process() const = 0;
		virtual void shutdown() {}
		virtual string serviceName() const = 0;

		KeyEvent onKeyDown() const { return mOnKeyDown; }
		KeyEvent onKeyUp() const { return mOnKeyUp; }

		bool isInitialised() const { return mInitialised; }

	protected:
		KeyEvent mOnKeyDown;
		KeyEvent mOnKeyUp;

		bool mInitialised;
	};
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
