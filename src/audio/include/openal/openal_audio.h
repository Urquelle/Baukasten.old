#ifndef OPENAL_AUDIO_H_EBPNAPHY
#define OPENAL_AUDIO_H_EBPNAPHY

#include "audio/Global"
#include "audio/IAudio"

struct ALCdevice_struct;
struct ALCcontext_struct;

namespace Baukasten {

	class OpenALData;
	typedef map<const string, OpenALData*> BufferMap;

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
		void play( const string&, int, int, bool );

		void pause( const string& );
		void stop( const string& );

	private:
		ALCdevice_struct*	m_device;
		ALCcontext_struct*	m_context;
		BufferMap			m_buffers;
		int					m_argc;
		char**				m_argv;
	};
} /* Baukasten */

#endif /* end of include guard: OPENAL_AUDIO_H_EBPNAPHY */

