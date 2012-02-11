#include "audio/AudioInterface"

#include "audio/AudioImpl"
#include "audio/IAudio"

using namespace Baukasten;

IAudio* AudioInterface::mInstance = 0;

IAudio*
AudioInterface::instance()
{
	if ( !mInstance ) {
		mInstance = new Audio();
	}

	return mInstance;
}
