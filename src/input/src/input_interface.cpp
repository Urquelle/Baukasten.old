#include "input_interface.h"

using namespace Baukasten;

InputInterface::InputInterface() :
	mEvent( new SDL_Event() )
{
}

InputInterface::~InputInterface()
{
}

InputEvent InputInterface::onEvent() const
{
	return mOnEvent;
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

	SDL_Surface *screen = SDL_SetVideoMode( 640, 480, 0, SDL_OPENGL );
}

void InputInterface::process() const
{
	SDL_PollEvent( mEvent );
	mOnEvent.emit( mEvent );

	if ( mEvent->type == SDL_KEYDOWN ) {
		mOnKeyDown.emit( mEvent->key.keysym.sym, mEvent->key.keysym.mod );
	}

	SDL_GL_SwapBuffers();
}

void InputInterface::shutDown()
{
	SDL_Quit();
}

