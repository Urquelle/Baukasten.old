#include "audio/AudioInterface"

#include "audio/AudioImpl"
#include "audio/IAudio"

using namespace Baukasten;

IAudio* AudioInterface::m_instance = 0;

IAudio*
AudioInterface::instance()
{
	if ( !m_instance ) {
		m_instance = new Audio();
	}

	return m_instance;
}
