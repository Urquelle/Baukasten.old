#include "input_interface.h"

#include <SDL/SDL.h>

#if defined( WITH_SDL )
#	include "sdl/sdl_interface.h"
#else
#	include "irrlicht/irrlicht_input.h"
#endif

using namespace Baukasten;

IInput* InputInterface::mInstance = 0;

IInput* InputInterface::instance()
{
	if ( !mInstance ) {
#if defined( WITH_SDL )
		mInstance = new SDLInterface();
#else
		mInstance = new IrrlichtInput();
#endif
	}

	return mInstance;
}

InputInterface::InputInterface()
{
}

InputInterface::~InputInterface()
{
}

