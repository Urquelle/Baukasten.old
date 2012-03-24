#include "audio/AudioImpl"

#include "core/CoreServices"
#include "core/Debug"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace Baukasten;

namespace Baukasten {

	struct OpenALData {
		string m_path;
		ALuint m_buffer;
		ALuint m_source;
	};

	typedef map<const string, OpenALData*> BufferMap;

	class OpenALAudioPrivate {
	public:
		OpenALAudioPrivate()
		{
		}

		virtual ~OpenALAudioPrivate()
		{
		}

		int
		init( int argc, char *argv[] )
		{
			alutInit( &argc, argv );

			m_device = alcOpenDevice( NULL );
			if ( !m_device )
				return 0;

			m_context = alcCreateContext( m_device, NULL );
			if ( !m_context )
				return 0;

			alcMakeContextCurrent( m_context );

			return 1;
		}

		void shutdown()
		{
			alcMakeContextCurrent( NULL );
			alcDestroyContext( m_context );
			alcCloseDevice( m_device );

			alutExit();

			OpenALData *data;
			for( auto i = m_buffers.begin(); i != m_buffers.end(); ++i ) {
				BK_DEBUG( "releasing OpenAL Data: " << i->first );
				data = i->second;

				alSourcei( data->m_source, AL_BUFFER, 0 );
				alDeleteBuffers( 1, &(data->m_buffer) );
				alDeleteSources( 1, &(data->m_source) );
			}
		}

		void
		loadFile( const string &path, const string &id )
		{
			BK_ASSERT( m_buffers.count( id ) == 0, "id " << id << " must be unique in the collection!" );

			ALuint buffer = alutCreateBufferFromFile( path.c_str() );
			ALuint source;

			alGenSources( 1, &source );
			alSourcei( source, AL_BUFFER, buffer );

			OpenALData *data = new OpenALData();

			data->m_buffer = buffer;
			data->m_source = source;
			data->m_path    =  path;

			m_buffers[ id ] = data;
		}

		void
		freeResource( const string &id )
		{
			OpenALData *data = m_buffers[ id ];

			if ( !data )
				return;

			alSourcei( data->m_source, AL_BUFFER, 0 );
			alDeleteBuffers( 1, &(data->m_buffer) );
			alDeleteSources( 1, &(data->m_source) );

			m_buffers.erase( id );
		}

		void
		play( const string &id, int from, int to, bool loop )
		{
			OpenALData *data = m_buffers[ id ];
			BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

			alSourcei( data->m_source, AL_LOOPING, loop );
			alSourcei( data->m_source, AL_SEC_OFFSET, from );
			alSourcePlay( data->m_source );
		}

		void
		pause( const string &id )
		{
			OpenALData *data = m_buffers[ id ];
			BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );
			alSourcePause( data->m_source );
		}

		void
		stop( const string &id )
		{
			OpenALData *data = m_buffers[ id ];
			BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );
			alSourceStop( data->m_source );
		}

		void
		setVolume( const string &id, const float volume )
		{
			OpenALData *data = m_buffers[ id ];
			BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

			alSourcef( data->m_source, AL_GAIN, volume );
		}

	private:
		ALCdevice*   m_device;
		ALCcontext*  m_context;
		BufferMap    m_buffers;
	};
}

OpenALAudio::OpenALAudio() :
	m_impl( new OpenALAudioPrivate() )
{
}

OpenALAudio::~OpenALAudio()
{
}

int
OpenALAudio::init( CoreServices *services )
{
	m_impl->init( services->argc(), services->argv() );
	m_initialised = true;
	return 1;
}

void
OpenALAudio::shutdown()
{
	m_impl->shutdown();
	m_initialised = false;
}

void
OpenALAudio::loadFile( const string &path, const string &id )
{
	if ( !m_initialised ) {
		BK_DEBUG( "loadFile called with uninitialised OpenAL environment!" );
		return;
	}

	m_impl->loadFile( path, id );
}

void
OpenALAudio::freeResource( const string &id )
{
	m_impl->freeResource( id );
}

void
OpenALAudio::setVolume( const string &id, const float volume )
{
	m_impl->setVolume( id, volume );
}

void
OpenALAudio::play( const string &id )
{
	play( id, false );
}

void
OpenALAudio::play( const string &id, bool loop )
{
	play( id, 0, 0, loop );
}

void
OpenALAudio::play( const string &id, int from, int to, bool loop )
{
	m_impl->play( id, from, to, loop );
}

void
OpenALAudio::pause( const string &id )
{
	m_impl->pause( id );
}

void
OpenALAudio::stop( const string &id )
{
	m_impl->stop( id );
}

