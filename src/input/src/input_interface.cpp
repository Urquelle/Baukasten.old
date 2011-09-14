#include "input_interface.h"

#include <SDL/SDL.h>

#include "irrlicht/irrlicht_input.h"

using namespace Baukasten;

IInput* InputInterface::mInstance = 0;

IInput* InputInterface::instance()
{
	if ( !mInstance ) {
		mInstance = new IrrlichtInput();
	}

	return mInstance;
}

InputInterface::InputInterface()
{
}

InputInterface::~InputInterface()
{
}

