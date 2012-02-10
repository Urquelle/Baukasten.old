#ifndef INPUTINTERFACE_AKBKP72C
#define INPUTINTERFACE_AKBKP72C

#include "core/Global"

#include <sigc++/sigc++.h>

namespace Baukasten {
	enum class Key {
		KEY_NONE,

		KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
		KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
		KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
		KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

		KEY_ARROW_LEFT, KEY_ARROW_UP, KEY_ARROW_RIGHT,
		KEY_ARROW_DOWN,

		KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
		KEY_7, KEY_8, KEY_9,

		KEY_SPACE, KEY_ESC,

		KEY_RETURN
	};

	enum class Modifier {
		KEYMOD_NONE			= 1u << 0,
		KEYMOD_LCTRL		= 1u << 1,
		KEYMOD_RCTRL		= 1u << 2,
		KEYMOD_CTRL			= 1u << 3,
		KEYMOD_LSHIFT		= 1u << 4,
		KEYMOD_RSHIFT		= 1u << 5,
		KEYMOD_SHIFT		= 1u << 6,
		KEYMOD_ALT			= 1u << 7
	};

	typedef sigc::signal<void, Key, Modifier> KeyEvent;

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
