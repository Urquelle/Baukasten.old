#ifndef AUDIO_INTERFACE_H_21IELBUV
#define AUDIO_INTERFACE_H_21IELBUV

namespace Baukasten {
	class IAudio;

	class AudioInterface {
	public:
		static IAudio* instance();
		virtual ~AudioInterface ();

	private:
		AudioInterface() {}

		static IAudio* mInstance;
	};
} /* Baukasten */

#endif /* end of include guard: AUDIO_INTERFACE_H_21IELBUV */

