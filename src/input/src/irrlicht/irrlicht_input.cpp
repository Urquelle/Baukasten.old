#include "irrlicht/irrlicht_input.h"

#include "core_services.h"
#include "debug.h"
#include "irrlicht/irrlicht_graphics.h"

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;

Key
getKey( EKEY_CODE key )
{
	Key t_key = Key::KEY_NONE;

	switch ( key ) {
	case KEY_KEY_A:
		t_key = Key::KEY_A;
		break;
	case KEY_KEY_B:
		t_key = Key::KEY_B;
		break;
	case KEY_KEY_C:
		t_key = Key::KEY_C;
		break;
	case KEY_KEY_D:
		t_key = Key::KEY_D;
		break;
	case KEY_KEY_E:
		t_key = Key::KEY_E;
		break;
	case KEY_KEY_F:
		t_key = Key::KEY_F;
		break;
	case KEY_KEY_G:
		t_key = Key::KEY_G;
		break;
	case KEY_KEY_H:
		t_key = Key::KEY_H;
		break;
	case KEY_KEY_I:
		t_key = Key::KEY_I;
		break;
	case KEY_KEY_J:
		t_key = Key::KEY_J;
		break;
	case KEY_KEY_K:
		t_key = Key::KEY_K;
		break;
	case KEY_KEY_L:
		t_key = Key::KEY_L;
		break;
	case KEY_KEY_M:
		t_key = Key::KEY_M;
		break;
	case KEY_KEY_N:
		t_key = Key::KEY_N;
		break;
	case KEY_KEY_O:
		t_key = Key::KEY_O;
		break;
	case KEY_KEY_P:
		t_key = Key::KEY_P;
		break;
	case KEY_KEY_Q:
		t_key = Key::KEY_Q;
		break;
	case KEY_KEY_R:
		t_key = Key::KEY_R;
		break;
	case KEY_KEY_S:
		t_key = Key::KEY_S;
		break;
	case KEY_KEY_T:
		t_key = Key::KEY_T;
		break;
	case KEY_KEY_U:
		t_key = Key::KEY_U;
		break;
	case KEY_KEY_V:
		t_key = Key::KEY_V;
		break;
	case KEY_KEY_W:
		t_key = Key::KEY_W;
		break;
	case KEY_KEY_X:
		t_key = Key::KEY_X;
		break;
	case KEY_KEY_Y:
		t_key = Key::KEY_Y;
		break;
	case KEY_KEY_Z:
		t_key = Key::KEY_Z;
		break;
	case KEY_LEFT:
		t_key = Key::KEY_ARROW_LEFT;
		break;
	case KEY_UP:
		t_key = Key::KEY_ARROW_UP;
		break;
	case KEY_RIGHT:
		t_key = Key::KEY_ARROW_RIGHT;
		break;
	case KEY_DOWN:
		t_key = Key::KEY_ARROW_DOWN;
		break;
	case irr::KEY_RETURN:
		t_key = Key::KEY_RETURN;
		break;
	}

	return t_key;
}

Modifier
getModifier( SEvent::SKeyInput key )
{
	Modifier mod = Modifier::KEYMOD_NONE;
	return mod;
}

// ---------- IrrlichtInputPrivate ------------ //
namespace Baukasten {
	class IrrlichtInputPrivate : public irr::IEventReceiver {
	public:
		IrrlichtInputPrivate( IrrlichtInput *input ) :
			mInput( input )
		{
		}

		~IrrlichtInputPrivate()
		{
		}

		bool
		OnEvent( const irr::SEvent &event )
		{
			switch ( event.EventType ) {
			case EET_KEY_INPUT_EVENT:
				if ( event.KeyInput.PressedDown ) {
					mInput->mOnKeyDown.emit(
						getKey( event.KeyInput.Key ),
						getModifier( event.KeyInput )
					);
				} else if ( !event.KeyInput.PressedDown ) {
					mInput->mOnKeyUp.emit(
						getKey( event.KeyInput.Key ),
						getModifier( event.KeyInput )
					);
				}
				break;
			}

			return false;
		}

	private:
		IrrlichtInput*	mInput;
	};
}

// ---------- IrrlichtInput ------------------ //
IrrlichtInput::IrrlichtInput() :
	IInput(),
	mImpl( new IrrlichtInputPrivate( this ) )
{
}

IrrlichtInput::~IrrlichtInput()
{
}

bool
IrrlichtInput::init( CoreServices *coreServices )
{
	BK_ASSERT( coreServices != 0, "coreServices must not be 0." );

	IrrlichtGraphics *graphics =
		dynamic_cast<IrrlichtGraphics*>( coreServices->getVideoService() );

	BK_ASSERT( graphics != 0, "graphics must not be 0." );
	graphics->getDevice()->setEventReceiver( mImpl.get() );
}

void
IrrlichtInput::process() const
{
}

void
IrrlichtInput::shutDown()
{
}

void
IrrlichtInput::setDevice( IrrlichtDevice *device )
{
	BK_ASSERT( device != 0, "device must not be 0." );
	mDevice = device;
}

