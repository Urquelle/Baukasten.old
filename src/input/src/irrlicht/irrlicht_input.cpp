#include "irrlicht/irrlicht_input.h"

#include "core_services.h"
#include "debug.h"
#include "irrlicht/irrlicht_graphics.h"

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;

Key getKey( EKEY_CODE key )
{
	Key t_key = KEY_NONE;

	switch ( key ) {
	case KEY_KEY_A:
		t_key = KEY_A;
		break;
	case KEY_KEY_B:
		t_key = KEY_B;
		break;
	case KEY_KEY_C:
		t_key = KEY_C;
		break;
	case KEY_KEY_D:
		t_key = KEY_D;
		break;
	case KEY_KEY_E:
		t_key = KEY_E;
		break;
	case KEY_KEY_F:
		t_key = KEY_F;
		break;
	case KEY_KEY_G:
		t_key = KEY_G;
		break;
	case KEY_KEY_H:
		t_key = KEY_H;
		break;
	case KEY_KEY_I:
		t_key = KEY_I;
		break;
	case KEY_KEY_J:
		t_key = KEY_J;
		break;
	case KEY_KEY_K:
		t_key = KEY_K;
		break;
	case KEY_KEY_L:
		t_key = KEY_L;
		break;
	case KEY_KEY_M:
		t_key = KEY_M;
		break;
	case KEY_KEY_N:
		t_key = KEY_N;
		break;
	case KEY_KEY_O:
		t_key = KEY_O;
		break;
	case KEY_KEY_P:
		t_key = KEY_P;
		break;
	case KEY_KEY_Q:
		t_key = KEY_Q;
		break;
	case KEY_KEY_R:
		t_key = KEY_R;
		break;
	case KEY_KEY_S:
		t_key = KEY_S;
		break;
	case KEY_KEY_T:
		t_key = KEY_T;
		break;
	case KEY_KEY_U:
		t_key = KEY_U;
		break;
	case KEY_KEY_V:
		t_key = KEY_V;
		break;
	case KEY_KEY_W:
		t_key = KEY_W;
		break;
	case KEY_KEY_X:
		t_key = KEY_X;
		break;
	case KEY_KEY_Y:
		t_key = KEY_Y;
		break;
	case KEY_KEY_Z:
		t_key = KEY_Z;
		break;
	case KEY_LEFT:
		t_key = KEY_ARROW_LEFT;
		break;
	case KEY_UP:
		t_key = KEY_ARROW_UP;
		break;
	case KEY_RIGHT:
		t_key = KEY_ARROW_RIGHT;
		break;
	case KEY_DOWN:
		t_key = KEY_ARROW_DOWN;
		break;
	}

	return t_key;
}

Modifier getModifier( SEvent::SKeyInput key )
{
	return KEYMOD_NONE;
}

IrrlichtInput::IrrlichtInput() :
	IInput()
{
}

IrrlichtInput::~IrrlichtInput()
{
}

bool IrrlichtInput::OnEvent( const SEvent &event )
{
	switch ( event.EventType ) {
	case EET_KEY_INPUT_EVENT:
		mOnKeyDown.emit(
			getKey( event.KeyInput.Key ),
			getModifier( event.KeyInput )
		);
		break;
	}

	return false;
}

bool IrrlichtInput::init( CoreServices *coreServices )
{
	BK_ASSERT( coreServices != 0, "coreServices must not be 0." );

	IrrlichtGraphics *graphics =
		dynamic_cast<IrrlichtGraphics*>( coreServices->getVideoService() );

	BK_ASSERT( graphics != 0, "graphics must not be 0." );
	graphics->getDevice()->setEventReceiver( this );
}

void IrrlichtInput::process() const
{
}

void IrrlichtInput::shutDown()
{
}

void IrrlichtInput::setDevice( IrrlichtDevice *device )
{
	BK_ASSERT( device != 0, "device must not be 0." );
	mDevice = device;
}

