#include "input/IInput"

using namespace Baukasten;

namespace Baukasten {
	class IInputPrivate {
	public:
		IInputPrivate( IInput *master ) :
			m_master( master ),
			m_onKeyDown( new KeyEvent() ),
			m_onKeyUp( new KeyEvent() ),
			m_initialised( false )
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

		bool
		isInitialised() const
		{
			return m_initialised;
		}

		void
		setInitialised( bool init )
		{
			m_initialised = init;
		}

	private:
		IInput *m_master;
		KeyEvent *m_onKeyDown;
		KeyEvent *m_onKeyUp;

		bool m_initialised;
	};
} /* Baukasten */

IInput::IInput() :
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

bool
IInput::isInitialised() const
{
	return m_impl->isInitialised();
}

void
IInput::setInitialised( bool init )
{
	m_impl->setInitialised( init );
}

