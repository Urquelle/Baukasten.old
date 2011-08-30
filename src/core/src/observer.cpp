#include "observer.h"

using namespace Baukasten;

Observer* Observer::mInstance = 0;

Observer* Observer::instance()
{
	if ( !mInstance )
		mInstance = new Observer();
	return mInstance;
}

Observer::Observer()
{
}

Observer::~Observer()
{
}
