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
	case KEY_KEY_A:			t_key = Key::KEY_A; break;
	case KEY_KEY_B:			t_key = Key::KEY_B; break;
	case KEY_KEY_C:			t_key = Key::KEY_C; break;
	case KEY_KEY_D:			t_key = Key::KEY_D; break;
	case KEY_KEY_E:			t_key = Key::KEY_E; break;
	case KEY_KEY_F:			t_key = Key::KEY_F; break;
	case KEY_KEY_G:			t_key = Key::KEY_G; break;
	case KEY_KEY_H:			t_key = Key::KEY_H; break;
	case KEY_KEY_I:			t_key = Key::KEY_I; break;
	case KEY_KEY_J:			t_key = Key::KEY_J; break;
	case KEY_KEY_K:			t_key = Key::KEY_K; break;
	case KEY_KEY_L:			t_key = Key::KEY_L; break;
	case KEY_KEY_M:			t_key = Key::KEY_M; break;
	case KEY_KEY_N:			t_key = Key::KEY_N; break;
	case KEY_KEY_O:			t_key = Key::KEY_O; break;
	case KEY_KEY_P:			t_key = Key::KEY_P; break;
	case KEY_KEY_Q:			t_key = Key::KEY_Q; break;
	case KEY_KEY_R:			t_key = Key::KEY_R; break;
	case KEY_KEY_S:			t_key = Key::KEY_S; break;
	case KEY_KEY_T:			t_key = Key::KEY_T; break;
	case KEY_KEY_U:			t_key = Key::KEY_U; break;
	case KEY_KEY_V:			t_key = Key::KEY_V; break;
	case KEY_KEY_W:			t_key = Key::KEY_W; break;
	case KEY_KEY_X:			t_key = Key::KEY_X; break;
	case KEY_KEY_Y:			t_key = Key::KEY_Y; break;
	case KEY_KEY_Z:			t_key = Key::KEY_Z; break;
	case KEY_LEFT:			t_key = Key::KEY_ARROW_LEFT; break;
	case KEY_UP:			t_key = Key::KEY_ARROW_UP; break;
	case KEY_RIGHT:			t_key = Key::KEY_ARROW_RIGHT; break;
	case KEY_DOWN:			t_key = Key::KEY_ARROW_DOWN; break;
	case KEY_RETURN:		t_key = Key::KEY_RETURN; break;
	case KEY_LBUTTON:		t_key = Key::KEY_NONE; break;
	case KEY_RBUTTON:		t_key = Key::KEY_NONE; break;
	case KEY_CANCEL:		t_key = Key::KEY_NONE; break;
	case KEY_MBUTTON:		t_key = Key::KEY_NONE; break;
	case KEY_XBUTTON1:		t_key = Key::KEY_NONE; break;
	case KEY_XBUTTON2:		t_key = Key::KEY_NONE; break;
	case KEY_BACK:			t_key = Key::KEY_NONE; break;
	case KEY_TAB:			t_key = Key::KEY_NONE; break;
	case KEY_CLEAR:			t_key = Key::KEY_NONE; break;
	case KEY_SHIFT:			t_key = Key::KEY_NONE; break;
	case KEY_CONTROL:		t_key = Key::KEY_NONE; break;
	case KEY_MENU:			t_key = Key::KEY_NONE; break;
	case KEY_PAUSE:			t_key = Key::KEY_NONE; break;
	case KEY_CAPITAL:		t_key = Key::KEY_NONE; break;
	case KEY_KANA:			t_key = Key::KEY_NONE; break;
	case KEY_JUNJA:			t_key = Key::KEY_NONE; break;
	case KEY_FINAL:			t_key = Key::KEY_NONE; break;
	case KEY_HANJA:			t_key = Key::KEY_NONE; break;
	case KEY_ESCAPE:		t_key = Key::KEY_NONE; break;
	case KEY_CONVERT:		t_key = Key::KEY_NONE; break;
	case KEY_NONCONVERT:	t_key = Key::KEY_NONE; break;
	case KEY_ACCEPT:		t_key = Key::KEY_NONE; break;
	case KEY_MODECHANGE:	t_key = Key::KEY_NONE; break;
	case KEY_SPACE:			t_key = Key::KEY_NONE; break;
	case KEY_PRIOR:			t_key = Key::KEY_NONE; break;
	case KEY_NEXT:			t_key = Key::KEY_NONE; break;
	case KEY_END:			t_key = Key::KEY_NONE; break;
	case KEY_HOME:			t_key = Key::KEY_NONE; break;
	case KEY_SELECT:		t_key = Key::KEY_NONE; break;
	case KEY_PRINT:			t_key = Key::KEY_NONE; break;
	case KEY_EXECUT:		t_key = Key::KEY_NONE; break;
	case KEY_SNAPSHOT:		t_key = Key::KEY_NONE; break;
	case KEY_INSERT:		t_key = Key::KEY_NONE; break;
	case KEY_DELETE:		t_key = Key::KEY_NONE; break;
	case KEY_HELP:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_0:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_1:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_2:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_3:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_4:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_5:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_6:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_7:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_8:			t_key = Key::KEY_NONE; break;
	case KEY_KEY_9:			t_key = Key::KEY_NONE; break;
	case KEY_LWIN:			t_key = Key::KEY_NONE; break;
	case KEY_RWIN:			t_key = Key::KEY_NONE; break;
	case KEY_APPS:			t_key = Key::KEY_NONE; break;
	case KEY_SLEEP:			t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD0:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD1:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD2:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD3:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD4:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD5:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD6:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD7:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD8:		t_key = Key::KEY_NONE; break;
	case KEY_NUMPAD9:		t_key = Key::KEY_NONE; break;
	case KEY_MULTIPLY:		t_key = Key::KEY_NONE; break;
	case KEY_ADD:			t_key = Key::KEY_NONE; break;
	case KEY_SEPARATOR:		t_key = Key::KEY_NONE; break;
	case KEY_SUBTRACT:		t_key = Key::KEY_NONE; break;
	case KEY_DECIMAL:		t_key = Key::KEY_NONE; break;
	case KEY_DIVIDE:		t_key = Key::KEY_NONE; break;
	case KEY_F1:			t_key = Key::KEY_NONE; break;
	case KEY_F2:			t_key = Key::KEY_NONE; break;
	case KEY_F3:			t_key = Key::KEY_NONE; break;
	case KEY_F4:			t_key = Key::KEY_NONE; break;
	case KEY_F5:			t_key = Key::KEY_NONE; break;
	case KEY_F6:			t_key = Key::KEY_NONE; break;
	case KEY_F7:			t_key = Key::KEY_NONE; break;
	case KEY_F8:			t_key = Key::KEY_NONE; break;
	case KEY_F9:			t_key = Key::KEY_NONE; break;
	case KEY_F10:			t_key = Key::KEY_NONE; break;
	case KEY_F11:			t_key = Key::KEY_NONE; break;
	case KEY_F12:			t_key = Key::KEY_NONE; break;
	case KEY_F13:			t_key = Key::KEY_NONE; break;
	case KEY_F14:			t_key = Key::KEY_NONE; break;
	case KEY_F15:			t_key = Key::KEY_NONE; break;
	case KEY_F16:			t_key = Key::KEY_NONE; break;
	case KEY_F17:			t_key = Key::KEY_NONE; break;
	case KEY_F18:			t_key = Key::KEY_NONE; break;
	case KEY_F19:			t_key = Key::KEY_NONE; break;
	case KEY_F20:			t_key = Key::KEY_NONE; break;
	case KEY_F21:			t_key = Key::KEY_NONE; break;
	case KEY_F22:			t_key = Key::KEY_NONE; break;
	case KEY_F23:			t_key = Key::KEY_NONE; break;
	case KEY_F24:			t_key = Key::KEY_NONE; break;
	case KEY_NUMLOCK:		t_key = Key::KEY_NONE; break;
	case KEY_SCROLL:		t_key = Key::KEY_NONE; break;
	case KEY_LSHIFT:		t_key = Key::KEY_NONE; break;
	case KEY_RSHIFT:		t_key = Key::KEY_NONE; break;
	case KEY_LCONTROL:		t_key = Key::KEY_NONE; break;
	case KEY_RCONTROL:		t_key = Key::KEY_NONE; break;
	case KEY_LMENU:			t_key = Key::KEY_NONE; break;
	case KEY_RMENU:			t_key = Key::KEY_NONE; break;
	case KEY_PLUS:			t_key = Key::KEY_NONE; break;
	case KEY_COMMA:			t_key = Key::KEY_NONE; break;
	case KEY_MINUS:			t_key = Key::KEY_NONE; break;
	case KEY_PERIOD:		t_key = Key::KEY_NONE; break;
	case KEY_ATTN:			t_key = Key::KEY_NONE; break;
	case KEY_CRSEL:			t_key = Key::KEY_NONE; break;
	case KEY_EXSEL:			t_key = Key::KEY_NONE; break;
	case KEY_EREOF:			t_key = Key::KEY_NONE; break;
	case KEY_PLAY:			t_key = Key::KEY_NONE; break;
	case KEY_ZOOM:			t_key = Key::KEY_NONE; break;
	case KEY_PA1:			t_key = Key::KEY_NONE; break;
	case KEY_OEM_CLEAR:		t_key = Key::KEY_NONE; break;
	case KEY_KEY_CODES_COUNT:		t_key = Key::KEY_NONE; break;
	case EET_GUI_EVENT:		t_key = Key::KEY_NONE; break;
	case EGUIET_FORCE_32_BIT:		t_key = Key::KEY_NONE; break;
	default:				t_key = Key::KEY_NONE; break;
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

	return true;
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

