#include "input_interface.h"

#include "glfw/glfw_input.h"

using namespace Baukasten;

IInput* InputInterface::mInstance = 0;

IInput*
InputInterface::instance()
{
	if ( !mInstance ) {
		mInstance = new GlfwInput();
	}

	return mInstance;
}

InputInterface::InputInterface()
{
}

InputInterface::~InputInterface()
{
}

