#include "audio/AudioImpl"

#include "core/Debug"
#include "services/Services"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace Baukasten;

namespace Baukasten {

	struct OpenALData {
		string m_id;
		string m_path;
		ALuint m_buffer;
		ALuint m_source;
		float  m_gain;
	};

	typedef map<const string, OpenALData*> BufferMap;

	class OpenALAudioPrivate {
	public:
		OpenALAudioPrivate( OpenALAudio *master ) :
			m_gainFactor( 1.0 ),
			m_master( master )
		{
		}

		virtual ~OpenALAudioPrivate()
		{
		}

		void
		init( int argc, char *argv[] )
		{
			alutInit( &argc, argv );

			m_device = alcOpenDevice( NULL );
			if ( !m_device )
				return;

			m_context = alcCreateContext( m_device, NULL );
			if ( !m_context )
				return;

			alcMakeContextCurrent( m_context );
			m_master->setIsReady( true );
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

		bool
		isReady() const
		{
			return m_ready;
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

			data->m_id      =  id;
			data->m_path    =  path;
			data->m_buffer  =  buffer;
			data->m_source  =  source;

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

			data->m_gain = volume;
			alSourcef( data->m_source, AL_GAIN, volume * m_gainFactor );
		}

		void
		setVolumeFactor( const float volume )
		{
			m_gainFactor = volume;
			OpenALData *data;
			for( auto i = m_buffers.begin(); i != m_buffers.end(); ++i ) {
				data = i->second;
				setVolume( data->m_id, data->m_gain );
			}
		}

		void
		setPosition( const string &id, const vec3<float> &pos )
		{
			OpenALData *data = m_buffers[ id ];
			BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

			ALfloat _pos[]{ pos[BK_X], pos[BK_Y], pos[BK_Z] };
			alSourcefv( data->m_source, AL_POSITION, _pos );
		}

		void
		setDirection( const string &id, const vec3<float> &dir )
		{
			OpenALData *data = m_buffers[ id ];
			BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

			ALfloat _dir[]{ dir[BK_X], dir[BK_Y], dir[BK_Z] };
			alSourcefv( data->m_source, AL_DIRECTION, _dir );
		}

	private:
		BufferMap    m_buffers;
		ALCcontext*  m_context;
		ALCdevice*   m_device;
		float        m_gainFactor;
		OpenALAudio* m_master;
		bool         m_ready;
	};
}

OpenALAudio::OpenALAudio() :
	IAudio( "OpenAL" ),
	m_impl( new OpenALAudioPrivate( this ) )
{
}

OpenALAudio::~OpenALAudio()
{
}

void
OpenALAudio::init( Services *services )
{
	m_impl->init( services->argc(), services->argv() );
}

void
OpenALAudio::shutdown()
{
	m_impl->shutdown();
}

void
OpenALAudio::loadFile( const string &path, const string &id )
{
	if ( !isReady() ) {
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
OpenALAudio::setVolumeFactor( const float factor )
{
	m_impl->setVolumeFactor( factor );
}

void
OpenALAudio::setPosition( const string &id, const vec3<float> &pos )
{
	m_impl->setPosition( id, pos );
}

void
OpenALAudio::setDirection( const string &id, const vec3<float> &dir )
{
	m_impl->setDirection( id, dir );
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
OpenALAudio::play( const string &id, u32 from, u32 to, bool loop )
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

