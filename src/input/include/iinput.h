#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "global.h"

#include "input_interface.h"

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT IInput {
	public:
		virtual bool init( CoreServices* ) = 0;
		virtual void process() const = 0;
		virtual void shutDown() = 0;

		KeyEvent onKeyDown() const { return mOnKeyDown; }
		KeyEvent onKeyUp() const { return mOnKeyUp; }

	protected:
		KeyEvent mOnKeyDown;
		KeyEvent mOnKeyUp;
	};
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
