#include "audio/AudioImpl"

#include "core/CoreServices"
#include "core/Debug"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace Baukasten;

namespace Baukasten {
	struct OpenALData {
		string m_filePath;
		ALuint m_buffer;
		ALuint m_source;
	};
} /* Baukasten */


OpenALAudio::OpenALAudio()
{
}

OpenALAudio::~OpenALAudio()
{
}

int
OpenALAudio::init( CoreServices *services )
{
	m_argc = services->argumentsCount();
	m_argv = services->arguments();

	alutInit( &m_argc, m_argv );

	m_device = alcOpenDevice( NULL );
	if ( !m_device )
		return 0;

	m_context = alcCreateContext( m_device, NULL );
	if ( !m_context )
		return 0;

	alcMakeContextCurrent( m_context );

	m_initialised = true;

	return 1;
}

void
OpenALAudio::shutdown()
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

	m_initialised = false;
}

void
OpenALAudio::loadFile( const string &filePath, const string &id )
{
	BK_ASSERT( m_buffers.count( id ) == 0, "id " << id << " must be unique in the collection!" );

	if ( !m_initialised ) {
		BK_DEBUG( "loadFile called with uninitialised OpenAL environment!" );
		return;
	}

	ALuint buffer = alutCreateBufferFromFile( filePath.c_str() );
	ALuint source;

	alGenSources( 1, &source );
	alSourcei( source, AL_BUFFER, buffer );

	OpenALData *data = new OpenALData();

	data->m_filePath = filePath;
	data->m_buffer = buffer;
	data->m_source = source;

	m_buffers[ id ] = data;
}

void
OpenALAudio::freeResource( const string &id )
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
	OpenALData *data = m_buffers[ id ];

	BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

	alSourcei( data->m_source, AL_LOOPING, loop );
	alSourcei( data->m_source, AL_SEC_OFFSET, from );

	alSourcePlay( data->m_source );
}

void
OpenALAudio::pause( const string &id )
{
	OpenALData *data = m_buffers[ id ];

	BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

	alSourcePause( data->m_source );
}

void
OpenALAudio::stop( const string &id )
{
	OpenALData *data = m_buffers[ id ];

	BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

	alSourceStop( data->m_source );
}

