#include "input_interface.h"

#include <SDL/SDL.h>

using namespace Baukasten;

Key getKey( SDLKey key )
{
	Key t_key = KEY_NONE;

	switch ( key ) {
	case SDLK_a:
		t_key = KEY_A;
		break;
	case SDLK_b:
		t_key = KEY_B;
		break;
	case SDLK_c:
		t_key = KEY_C;
		break;
	case SDLK_d:
		t_key = KEY_D;
		break;
	case SDLK_e:
		t_key = KEY_E;
		break;
	case SDLK_f:
		t_key = KEY_F;
		break;
	case SDLK_g:
		t_key = KEY_G;
		break;
	case SDLK_h:
		t_key = KEY_H;
		break;
	case SDLK_i:
		t_key = KEY_I;
		break;
	case SDLK_j:
		t_key = KEY_J;
		break;
	case SDLK_k:
		t_key = KEY_K;
		break;
	case SDLK_l:
		t_key = KEY_L;
		break;
	case SDLK_m:
		t_key = KEY_M;
		break;
	case SDLK_n:
		t_key = KEY_N;
		break;
	case SDLK_o:
		t_key = KEY_O;
		break;
	case SDLK_p:
		t_key = KEY_P;
		break;
	case SDLK_q:
		t_key = KEY_Q;
		break;
	case SDLK_r:
		t_key = KEY_R;
		break;
	case SDLK_s:
		t_key = KEY_S;
		break;
	case SDLK_t:
		t_key = KEY_T;
		break;
	case SDLK_u:
		t_key = KEY_U;
		break;
	case SDLK_v:
		t_key = KEY_V;
		break;
	case SDLK_w:
		t_key = KEY_W;
		break;
	case SDLK_x:
		t_key = KEY_X;
		break;
	case SDLK_y:
		t_key = KEY_Y;
		break;
	case SDLK_z:
		t_key = KEY_Z;
		break;
	}

	return t_key;
}

Modifier getModifier( SDLMod mod )
{
	return KEYMOD_NONE;
}

InputInterface::InputInterface()
{
}

InputInterface::~InputInterface()
{
}

KeyDownEvent InputInterface::onKeyDown() const
{
	return mOnKeyDown;
}

bool InputInterface::init()
{
	if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
		return false;
	}

	SDL_Surface *screen = SDL_SetVideoMode( 1024, 768, 0, SDL_OPENGL );
}

void InputInterface::process() const
{
	SDL_Event event;

	while ( SDL_PollEvent( &event ) ) {
		switch( event.type ) {
		case SDL_KEYDOWN:
			mOnKeyDown.emit(
				getKey( event.key.keysym.sym ),
				getModifier( event.key.keysym.mod )
			);
			break;
		default:
			break;
		}
	}

	SDL_GL_SwapBuffers();
}

void InputInterface::shutDown()
{
	SDL_Quit();
}

