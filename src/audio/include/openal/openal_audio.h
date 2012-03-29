#ifndef OPENAL_AUDIO_H_EBPNAPHY
#define OPENAL_AUDIO_H_EBPNAPHY

#include "audio/Global"
#include "audio/IAudio"

namespace Baukasten {

	class OpenALAudioPrivate;

	/*!
	 * \brief class implementing the IAudio interface.
	 * \ingroup services audio
	 * \headerfile AudioImpl "audio/AudioImpl"
	 *
	 * using the OpenAL library, this class implements the IAudio interface
	 * providing all the basic methods to play back audio resources.
	 *
	 * \note the implementation classes are not supposed to be used directly. use
	 * the according method to retrieve the audio interface in the Services class.
	 *
	 * \sa AudioInterface::instance()
	 * \sa Services::audioService()
	 */
	class OpenALAudio : public IAudio {
	public:

		/*! \brief constructor */
		OpenALAudio();

		/*! destructor */
		virtual ~OpenALAudio();

		/*! \sa IAudio::init() */
		void init( Services* );

		/*! \sa IAudio::shutdown() */
		void shutdown();

		/*! \sa IAudio::loadFile() */
		void loadFile( const string&, const string& );

		/*! \sa IAudio::freeResource() */
		void freeResource( const string& );

		/*! \sa IAudio::setVolume() */
		void setVolume( const string&, const float );

		/*! \sa IAudio::setVolumeFactor() */
		void setVolumeFactor( const float );

		/*! \sa IAudio::setPosition() */
		void setPosition( const string&, const vec3<float>& );

		/*! \sa IAudio::setLoop() */
		void setLoop( const string&, bool );

		/*! \sa IAudio::setDirection() */
		void setDirection( const string&, const vec3<float>& );

		/*! \sa IAudio::play( const string& ) */
		void play( const string& );

		/*! \sa IAudio::play( const string&, u32, u32, bool ) */
		void play( const string&, u32, u32 );

		/*! \sa IAudio::pause() */
		void pause( const string& );

		/*! \sa IAudio::stop() */
		void stop( const string& );

	private:
		BK_PIMPL_PTR( OpenALAudio );
	};
} /* Baukasten */

#endif /* end of include guard: OPENAL_AUDIO_H_EBPNAPHY */

