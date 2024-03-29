#include "input/InputImpl"

#include "core/Debug"
#include "graphics/IGraphics"
#include "services/Services"

#include "input/include/glfw/glfw_input_helper.h"

const char *SERVICE_NAME = "GLFW";

using namespace Baukasten;

void GLFWCALL inputHandler( int key, int state )
{
	auto &service = Services::instance().inputService();

	if ( service.name() != SERVICE_NAME )
		return;

	if ( state == GLFW_PRESS )
		service.onKeyDown()->emit( _key( key ), _modifier( key ) );
	else if ( state == GLFW_RELEASE )
		service.onKeyUp()->emit( _key( key ), _modifier( key ) );
}

GlfwInput::GlfwInput() :
	IInput( SERVICE_NAME )
{
}

GlfwInput::~GlfwInput()
{
}

void
GlfwInput::init( Services &service )
{
	if ( service.graphicsService().name() != SERVICE_NAME )
		BK_ERROR( "incompatible video backend!" );

	// for the callback to work the window
	// must have already been created
	glfwSetKeyCallback( inputHandler );
	glfwEnable( GLFW_KEY_REPEAT );
	setIsReady( true );
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
	setIsReady( false );
}

