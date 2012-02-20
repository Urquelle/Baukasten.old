#ifndef AUDIO_INTERFACE_H_21IELBUV
#define AUDIO_INTERFACE_H_21IELBUV

#include "audio/Global"

namespace Baukasten {
	class IAudio;

	class BAUKASTEN_EXPORT AudioInterface {
	public:
		static IAudio* instance();
		virtual ~AudioInterface ();

	private:
		AudioInterface() {}

		static IAudio* m_instance;
	};
} /* Baukasten */

#endif /* end of include guard: AUDIO_INTERFACE_H_21IELBUV */

