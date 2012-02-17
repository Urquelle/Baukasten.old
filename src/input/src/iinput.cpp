#include "input/IInput"

using namespace Baukasten;

namespace Baukasten {
	class IInputPrivate {
	public:
		IInputPrivate( IInput *master ) :
			mMaster( master ),
			mOnKeyDown( new KeyEvent() ),
			mOnKeyUp( new KeyEvent() ),
			mInitialised( false )
		{
		}

		virtual ~IInputPrivate()
		{
			delete mOnKeyDown;
			delete mOnKeyUp;
		}

		KeyEvent*
		onKeyDown()
		{
			return mOnKeyDown;
		}

		KeyEvent*
		onKeyUp()
		{
			return mOnKeyUp;
		}

		bool
		isInitialised() const
		{
			return mInitialised;
		}

		void
		setInitialised( bool init )
		{
			mInitialised = init;
		}

	private:
		IInput *mMaster;
		KeyEvent *mOnKeyDown;
		KeyEvent *mOnKeyUp;

		bool mInitialised;
	};
} /* Baukasten */

IInput::IInput() :
	mImpl( new IInputPrivate( this ) )
{
}

Baukasten::KeyEvent*
IInput::onKeyDown()
{
	return mImpl->onKeyDown();
}

Baukasten::KeyEvent*
IInput::onKeyUp()
{
	return mImpl->onKeyUp();
}

bool
IInput::isInitialised() const
{
	return mImpl->isInitialised();
}

void
IInput::setInitialised( bool init )
{
	mImpl->setInitialised( init );
}

