#ifndef GLOBAL_H_SEZP3I7H
#define GLOBAL_H_SEZP3I7H

/*!
 * \file input/include/global.h
 * \brief global include file for Input module.
 *
 * this file contains all the basic declarations that
 * are used across the input module.
 */

/*! \defgroup input Input */

#include "core/Global"

#include <sigc++/sigc++.h>
#include <string>

namespace Baukasten {
	using namespace std;

	/*! possible states of a key. */
	enum KeyState {
		PRESSED, RELEASED
	};

	/*! all keys recognised by the Input interface. */
	enum Key {
		KEY_NONE = 0,

		KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6,
		KEY_7, KEY_8, KEY_9,

		KEY_A = 65,   KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G,
		KEY_H,        KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
		KEY_O,        KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U,
		KEY_V,        KEY_W, KEY_X, KEY_Y, KEY_Z,

		KEY_ARROW_LEFT, KEY_ARROW_UP, KEY_ARROW_RIGHT,
		KEY_ARROW_DOWN,

		KEY_SPACE, KEY_ESC,

		KEY_DIVIDE, KEY_MULTIPLY, KEY_SUBTRACT, KEY_ADD,
		KEY_DECIMAL, KEY_EQUAL, KEY_ENTER
	};

	/*! all modifier keys recognised by the Input interface. */
	enum Modifier {
		KEYMOD_NONE			= 1u << 0,
		KEYMOD_LCTRL		= 1u << 1,
		KEYMOD_RCTRL		= 1u << 2,
		KEYMOD_CTRL			= 1u << 3,
		KEYMOD_LSHIFT		= 1u << 4,
		KEYMOD_RSHIFT		= 1u << 5,
		KEYMOD_SHIFT		= 1u << 6,
		KEYMOD_ALT			= 1u << 7
	};

	/*! keyEvent signal. */
	typedef sigc::signal<void, Key, Modifier> KeyEvent;

} /* Baukasten */

#endif /* end of include guard: GLOBAL_H_SEZP3I7H */

