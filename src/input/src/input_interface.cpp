#include "input/InputInterface"

#include "input/InputImpl"

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

