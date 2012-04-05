#ifndef GLFW_INPUT_FUNCTIONS_H_8A4UFMBF
#define GLFW_INPUT_FUNCTIONS_H_8A4UFMBF

#include "input/InputImpl"

#include <GL/glfw.h>

using namespace Baukasten;

static Key
_key( int key )
{
	Key t_key = Key::KEY_NONE;

	switch ( key ) {
	case 'A': t_key = Key::KEY_A; break;
	case 'B': t_key = Key::KEY_B; break;
	case 'C': t_key = Key::KEY_C; break;
	case 'D': t_key = Key::KEY_D; break;
	case 'E': t_key = Key::KEY_E; break;
	case 'F': t_key = Key::KEY_F; break;
	case 'G': t_key = Key::KEY_G; break;
	case 'H': t_key = Key::KEY_H; break;
	case 'I': t_key = Key::KEY_I; break;
	case 'J': t_key = Key::KEY_J; break;
	case 'K': t_key = Key::KEY_K; break;
	case 'L': t_key = Key::KEY_L; break;
	case 'M': t_key = Key::KEY_M; break;
	case 'N': t_key = Key::KEY_N; break;
	case 'O': t_key = Key::KEY_O; break;
	case 'P': t_key = Key::KEY_P; break;
	case 'Q': t_key = Key::KEY_Q; break;
	case 'R': t_key = Key::KEY_R; break;
	case 'S': t_key = Key::KEY_S; break;
	case 'T': t_key = Key::KEY_T; break;
	case 'U': t_key = Key::KEY_U; break;
	case 'V': t_key = Key::KEY_V; break;
	case 'W': t_key = Key::KEY_W; break;
	case 'X': t_key = Key::KEY_X; break;
	case 'Y': t_key = Key::KEY_Y; break;
	case 'Z': t_key = Key::KEY_Z; break;

	case GLFW_KEY_SPACE:	t_key = Key::KEY_SPACE; break;
	case GLFW_KEY_UP:		t_key = Key::KEY_ARROW_UP; break;
	case GLFW_KEY_DOWN:		t_key = Key::KEY_ARROW_DOWN; break;
	case GLFW_KEY_RIGHT:	t_key = Key::KEY_ARROW_RIGHT; break;
	case GLFW_KEY_LEFT:		t_key = Key::KEY_ARROW_LEFT; break;
	case GLFW_KEY_ESC:		t_key = Key::KEY_ESC; break;
	case GLFW_KEY_F1:
	case GLFW_KEY_F2:
	case GLFW_KEY_F3:
	case GLFW_KEY_F4:
	case GLFW_KEY_F5:
	case GLFW_KEY_F6:
	case GLFW_KEY_F7:
	case GLFW_KEY_F8:
	case GLFW_KEY_F9:
	case GLFW_KEY_F10:
	case GLFW_KEY_F11:
	case GLFW_KEY_F12:
	case GLFW_KEY_F13:
	case GLFW_KEY_F14:
	case GLFW_KEY_F15:
	case GLFW_KEY_F16:
	case GLFW_KEY_F17:
	case GLFW_KEY_F18:
	case GLFW_KEY_F19:
	case GLFW_KEY_F20:
	case GLFW_KEY_F21:
	case GLFW_KEY_F22:
	case GLFW_KEY_F23:
	case GLFW_KEY_F24:
	case GLFW_KEY_F25:
	case GLFW_KEY_LSHIFT:
	case GLFW_KEY_RSHIFT:
	case GLFW_KEY_LCTRL:
	case GLFW_KEY_RCTRL:
	case GLFW_KEY_LALT:
	case GLFW_KEY_RALT:
	case GLFW_KEY_TAB:
	case GLFW_KEY_ENTER:
	case GLFW_KEY_BACKSPACE:
	case GLFW_KEY_INSERT:
	case GLFW_KEY_DEL:
	case GLFW_KEY_PAGEUP:
	case GLFW_KEY_PAGEDOWN:
	case GLFW_KEY_HOME:
	case GLFW_KEY_END:
	case GLFW_KEY_KP_0:
	case GLFW_KEY_KP_1:
	case GLFW_KEY_KP_2:
	case GLFW_KEY_KP_3:
	case GLFW_KEY_KP_4:
	case GLFW_KEY_KP_5:
	case GLFW_KEY_KP_6:
	case GLFW_KEY_KP_7:
	case GLFW_KEY_KP_8:
	case GLFW_KEY_KP_9:
	case GLFW_KEY_KP_DIVIDE:
	case GLFW_KEY_KP_MULTIPLY:
	case GLFW_KEY_KP_SUBTRACT:
	case GLFW_KEY_KP_ADD:
	case GLFW_KEY_KP_DECIMAL:
	case GLFW_KEY_KP_EQUAL:
	case GLFW_KEY_KP_ENTER:
		t_key = Key::KEY_NONE; break;
	default: t_key = Key::KEY_NONE; break;
	}

	return t_key;
}

static Modifier
_modifier( int key )
{
	Modifier mod = Modifier::KEYMOD_NONE;
	return mod;
}

#endif /* end of include guard: GLFW_INPUT_FUNCTIONS_H_8A4UFMBF */

