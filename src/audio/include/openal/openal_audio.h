#ifndef OPENAL_AUDIO_H_EBPNAPHY
#define OPENAL_AUDIO_H_EBPNAPHY

#include "global.h"

#include "iaudio.h"

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
		ALCdevice_struct*	mDevice;
		ALCcontext_struct*	mContext;
		BufferMap			mBuffers;
		int					mArgc;
		char**				mArgv;
	};
} /* Baukasten */

#endif /* end of include guard: OPENAL_AUDIO_H_EBPNAPHY */

