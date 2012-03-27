#ifndef IAUDIO_H_YOASQ2PU
#define IAUDIO_H_YOASQ2PU

#include "audio/AudioInterface"
#include "audio/Global"

namespace Baukasten {

	class CoreServices;

	/*! \brief Audio Interface declaration.
	 *
	 * \ingroup audio interface
	 *
	 * defines methods which an implementation class has to
	 * implement in order to be used as Audio Service.
	 */
	class BAUKASTEN_EXPORT IAudio {
	public:
		/*! constructor */
		IAudio() : m_initialised( false ) {}

		/*! \brief initialises the audio service.
		 *
		 * do everything in this method to initialise
		 * the audio service.
		 *
		 * \param services CoreServices pointer.
		 * \return 1 if initialisation successfull, 0 otherwise.
		 */
		virtual int init( CoreServices *services ) = 0;

		/*! \brief shutdown the audio service.
		 *
		 * shutdown the audio service.
		 */
		virtual void shutdown() = 0;

		/*! \brief loads an audio file for later use.
		 *
		 * loads an audio file with the given path, and stores
		 * it for later use with the given id.
		 *
		 * the supported file types depend on the used backend.
		 * openal is used for current implementation.
		 *
		 * \warning id has to be unique, otherwise the application will simply exit
		 * with a message in the stdout in debug mode.
		 *
		 * \param path path to the audio file.
		 * \param id id of the audio resource.
		 */
		virtual void loadFile( const string &path, const string &id ) = 0;

		/*! \brief remove given resource from the list of available resources.
		 *
		 * removes the given resource from the list of available resources. it
		 * is safe to remove resources that do not exist, in this case nothing
		 * happens.
		 *
		 * the given id is freed and can be used in the subsequent call to
		 * loadFile().
		 */
		virtual void freeResource( const string& ) = 0;

		/*! \brief set volume value.
		 *
		 * set the value of the volume for the resource
		 * identified by id.
		 *
		 * NOTE: value has to be in the range [0, 1].
		 *
		 * \param id of the resource
		 * \param volume value to be set
		 */
		virtual void setVolume( const string &id, const float volume ) = 0;
		virtual void setVolumeFactor( const float ) = 0;

		virtual void play( const string& ) = 0;
		virtual void play( const string&, bool ) = 0;
		virtual void play( const string&, u32, u32, bool ) = 0;

		virtual void pause( const string& ) = 0;
		virtual void stop( const string& ) = 0;

	protected:
		bool m_initialised;
	};
} /* Baukasten */

#endif /* end of include guard: IAUDIO_H_YOASQ2PU */

