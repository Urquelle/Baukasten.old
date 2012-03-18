#ifndef OPENAL_AUDIO_H_EBPNAPHY
#define OPENAL_AUDIO_H_EBPNAPHY

#include "audio/Global"
#include "audio/IAudio"

namespace Baukasten {

	class OpenALAudioPrivate;

	class OpenALAudio : public IAudio {
	public:
		OpenALAudio();
		virtual ~OpenALAudio();

		int init( CoreServices* );
		void shutdown();

		void loadFile( const string&, const string& );
		void freeResource( const string& );

		void play( const string& );
		void play( const string&, bool );
		void play( const string&, u32, u32, bool );

		void pause( const string& );
		void stop( const string& );

	private:
		BK_PIMPL_PTR( OpenALAudio );
	};
} /* Baukasten */

#endif /* end of include guard: OPENAL_AUDIO_H_EBPNAPHY */

