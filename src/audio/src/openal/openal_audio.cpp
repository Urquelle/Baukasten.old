#include "audio/AudioImpl"

#include <core/CoreServices>
#include <core/Debug>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace Baukasten;

namespace Baukasten {
	struct OpenALData {
		string mFilePath;
		ALuint mBuffer;
		ALuint mSource;
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
	mArgc = services->getArgumentsCount();
	mArgv = services->getArguments();

	alutInit( &mArgc, mArgv );

	mDevice = alcOpenDevice( NULL );
	if ( !mDevice )
		return 0;

	mContext = alcCreateContext( mDevice, NULL );
	if ( !mContext )
		return 0;

	alcMakeContextCurrent( mContext );

	mInitialised = true;

	return 1;
}

void
OpenALAudio::shutdown()
{
	alcMakeContextCurrent( NULL );
	alcDestroyContext( mContext );
	alcCloseDevice( mDevice );

	alutExit();

	OpenALData *data;
	for( auto i = mBuffers.begin(); i != mBuffers.end(); ++i ) {
		BK_DEBUG( "releasing OpenAL Data: " << i->first );
		data = i->second;

		alSourcei( data->mSource, AL_BUFFER, 0 );
		alDeleteBuffers( 1, &(data->mBuffer) );
		alDeleteSources( 1, &(data->mSource) );
	}

	mInitialised = false;
}

void
OpenALAudio::loadFile( const string &filePath, const string &id )
{
	BK_ASSERT( mBuffers.count( id ) == 0, "id " << id << " must be unique in the collection!" );

	if ( !mInitialised ) {
		BK_DEBUG( "loadFile called with uninitialised OpenAL environment!" );
		return;
	}

	ALuint buffer = alutCreateBufferFromFile( filePath.c_str() );
	ALuint source;

	alGenSources( 1, &source );
	alSourcei( source, AL_BUFFER, buffer );

	OpenALData *data = new OpenALData();

	data->mFilePath = filePath;
	data->mBuffer = buffer;
	data->mSource = source;

	mBuffers[ id ] = data;
}

void
OpenALAudio::freeResource( const string &id )
{
	OpenALData *data = mBuffers[ id ];

	if ( !data )
		return;

	alSourcei( data->mSource, AL_BUFFER, 0 );
	alDeleteBuffers( 1, &(data->mBuffer) );
	alDeleteSources( 1, &(data->mSource) );

	mBuffers.erase( id );
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
	OpenALData *data = mBuffers[ id ];

	BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

	alSourcei( data->mSource, AL_LOOPING, loop );
	alSourcei( data->mSource, AL_SEC_OFFSET, from );

	alSourcePlay( data->mSource );
}

void
OpenALAudio::pause( const string &id )
{
	OpenALData *data = mBuffers[ id ];

	BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

	alSourcePause( data->mSource );
}

void
OpenALAudio::stop( const string &id )
{
	OpenALData *data = mBuffers[ id ];

	BK_ASSERT( data != NULL, "nothing with the given id " << id << " could be found!" );

	alSourceStop( data->mSource );
}

