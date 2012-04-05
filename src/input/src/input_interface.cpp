#include "input/InputInterface"

#include "input/InputImpl"

using namespace Baukasten;

IInput* InputInterface::m_instance = 0;

IInput*
InputInterface::instance()
{
	if ( !m_instance ) {
		m_instance = new Input();
	}

	return m_instance;
}

InputInterface::InputInterface()
{
}

