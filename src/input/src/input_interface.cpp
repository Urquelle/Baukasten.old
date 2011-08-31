#include "input_interface.h"

#include <SDL/SDL.h>

#if defined( WITH_SDL )
#	include "sdl/sdl_interface.h"
#endif

using namespace Baukasten;

IInput* InputInterface::mInstance = 0;

IInput* InputInterface::instance()
{
	if ( !mInstance ) {
#if defined( WITH_SDL )
		mInstance = new SDLInterface();
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
