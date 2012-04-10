#include "input/InputImpl"

#include "core/Debug"
#include "graphics/IGraphics"
#include "services/Services"

#include "input/include/glfw/glfw_input_helper.h"

using namespace Baukasten;

void GLFWCALL inputHandler( int key, int state )
{
	auto &service = Services::instance().inputService();

	if ( service.name() != "GLFW" )
		return;

	if ( state == GLFW_PRESS )
		service.onKeyDown()->emit( _key( key ), _modifier( key ) );
	else if ( state == GLFW_RELEASE )
		service.onKeyUp()->emit( _key( key ), _modifier( key ) );
}

GlfwInput::GlfwInput() :
	IInput( "GLFW" )
{
}

GlfwInput::~GlfwInput()
{
}

void
GlfwInput::init( Services &service )
{
	if ( service.videoService().name() != "GLFW" )
		BK_ERROR( "incompatible video backend!" );

	if ( !service.videoService().isReady() )
		BK_ERROR( "video service must be initialised." );

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

