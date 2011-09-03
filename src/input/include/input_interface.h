#ifndef INPUTINTERFACE_AKBKP72C
#define INPUTINTERFACE_AKBKP72C

#include "global.h"

#include <sigc++/sigc++.h>

namespace Baukasten {
	typedef enum {
		KEY_NONE,
		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
		KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
		KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
		KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

		KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
		KEY_7, KEY_8, KEY_9
	} Key;

	typedef enum {
		KEYMOD_NONE,
		KEYMOD_LCTRL, KEYMOD_RCTRL, KEYMOD_CTRL,
		KEYMOD_LSHIFT, KEYMOD_RSHIFT, KEYMOD_SHIFT,
		KEYMOD_ALT
	} Modifier;

	typedef sigc::signal<void, Key, Modifier> KeyDownEvent;

	class IInput;

	class BAUKASTEN_EXPORT InputInterface {
	public:
		static IInput* instance();

		virtual ~InputInterface();

	private:
		InputInterface();

		static IInput* mInstance;
	};
} /* Baukasten */

#endif /* end of include guard: INPUTINTERFACE_AKBKP72C */
