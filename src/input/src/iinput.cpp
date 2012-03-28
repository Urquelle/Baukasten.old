#include "input/IInput"

using namespace Baukasten;

namespace Baukasten {
	class IInputPrivate {
	public:
		IInputPrivate( IInput *master ) :
			m_master( master ),
			m_onKeyDown( new KeyEvent() ),
			m_onKeyUp( new KeyEvent() )
		{
		}

		virtual ~IInputPrivate()
		{
			delete m_onKeyDown;
			delete m_onKeyUp;
		}

		KeyEvent*
		onKeyDown()
		{
			return m_onKeyDown;
		}

		KeyEvent*
		onKeyUp()
		{
			return m_onKeyUp;
		}

	private:
		IInput *m_master;
		KeyEvent *m_onKeyDown;
		KeyEvent *m_onKeyUp;

		bool m_initialised;
	};
} /* Baukasten */

IInput::IInput( const string &name ) :
	IService( name ),
	m_impl( new IInputPrivate( this ) )
{
}

Baukasten::KeyEvent*
IInput::onKeyDown()
{
	return m_impl->onKeyDown();
}

Baukasten::KeyEvent*
IInput::onKeyUp()
{
	return m_impl->onKeyUp();
}

