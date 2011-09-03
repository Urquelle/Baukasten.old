#ifndef IINPUT_EQ5AS93H
#define IINPUT_EQ5AS93H

#include "global.h"

#include "input_interface.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT IInput {
	public:
		virtual bool init() = 0;
		virtual void process() const = 0;
		virtual void shutDown() = 0;

		KeyDownEvent onKeyDown() const { return mOnKeyDown; }

	protected:
		KeyDownEvent mOnKeyDown;
	};
} /* Baukasten */

#endif /* end of include guard: IINPUT_EQ5AS93H */
