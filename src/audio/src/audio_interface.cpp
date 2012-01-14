#include "audio_interface.h"
#include "iaudio.h"

#include "openal/openal_audio.h"

using namespace Baukasten;

IAudio* AudioInterface::mInstance = 0;

IAudio*
AudioInterface::instance()
{
	if ( !mInstance ) {
		mInstance = new OpenALAudio();
	}

	return mInstance;
}
