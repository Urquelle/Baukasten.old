#include "input/InputImpl"

#include "core/CoreServices"
#include "core/Debug"
#include "graphics/IGraphics"

#include "input/include/glfw/glfw_input_functions.h"

using namespace Baukasten;

void GLFWCALL inputHandler( int key, int state )
{
	auto service = static_cast<GlfwInput*>(
			CoreServices::instance()->inputService() );

	if ( service->serviceName() != "GLFW" )
		return;

	if ( state == GLFW_PRESS )
		service->onKeyDown()->emit( _key( key ), _modifier( key ) );
	else if ( state == GLFW_RELEASE )
		service->onKeyUp()->emit( _key( key ), _modifier( key ) );
}

GlfwInput::GlfwInput()
{
}

GlfwInput::~GlfwInput()
{
}

bool
GlfwInput::init( CoreServices* )
{
	// for the callback to work the window
	// must have already been created
	glfwSetKeyCallback( inputHandler );
	glfwEnable( GLFW_KEY_REPEAT );
	setInitialised( true );
	return true;
}

KeyState
GlfwInput::keyState( const Key key ) const
{
	return ( glfwGetKey( (int)key ) == GLFW_PRESS )
		? KeyState::PRESSED
		: KeyState::RELEASED;
}

void
GlfwInput::process() const
{
}

void
GlfwInput::shutdown()
{
	setInitialised( false );
}

