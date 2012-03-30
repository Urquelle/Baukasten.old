#pragma once

#include "audio/AudioInterface"
#include "audio/Global"
#include "core/Math"
#include "services/IService"

namespace Baukasten {

	class Services;

	/*!
	 * \brief audio interface declaration.
	 * \ingroup services audio interface
	 * \headerfile IAudio "audio/IAudio"
	 *
	 * defines methods which an implementation class has to
	 * implement in order to be used as Audio Service.
	 *
	 * \todo needs further improvement such as:
	 * 	- ability to create a source.
	 * 	- set attributes per source (loop, from, to, volume, ...)
	 * 	- change the "to" attribute to "duration"
	 */
	class BAUKASTEN_EXPORT IAudio : public IService {
	public:

		/*!
		 * \brief constructor.
		 *
		 * basic constructor of the class.
		 *
		 * \param name name of the service.
		 */
		IAudio( const string &name ) : IService( name ) {}

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

		/*!
		 * \brief set global volume factor.
		 *
		 * in order for being able to control global volume, this method
		 * provides the possibility to set the global volume factor.
		 *
		 * the volume value of every source is multiplied by this factor.
		 *
		 * \param factor float value in the range [0, 1].
		 */
		virtual void setVolumeFactor( const float factor ) = 0;

		/*!
		 * \brief set the position of the audio source.
		 *
		 * sets the 3d position of the audio source.
		 *
		 * \param id key under which the audio resource is stored in the collection.
		 * \param position position of the audio source in the game space.
		 */
		virtual void setPosition( const string &id, const vec3<float> &position ) = 0;

		/*!
		 * \brief set the direction of the audio source.
		 *
		 * sets the direction of the audio source.
		 *
		 * \param id key under which the audio resource is stored in the collection.
		 * \param direction direction of the audio source in the game space.
		 */
		virtual void setDirection( const string &id, const vec3<float> &direction ) = 0;

		/*!
		 * \brief set whether the audio resource's playback should be looped.
		 *
		 * sets the loop property of the source, which tells the service whether
		 * to start the source all over again, once the end is reached.
		 *
		 * \param id key under which the audio resource is stored in the collection.
		 * \param loop loop flag.
		 */
		virtual void setLoop( const string &id, bool loop ) = 0;

		/*!
		 * \brief play audio resource from the collection.
		 *
		 * plays an audio resource from the collection with the
		 * given id. plays the resource from the beginning to the
		 * end, and only once.
		 *
		 * \param id key under which the resource is stored in the collection.
		 */
		virtual void play( const string &id ) = 0;

		/*!
		 * \brief play audio resource from the collection.
		 *
		 * plays an audio resource from the collection with the given id. the
		 * additional arguments tell the service where to start playing the
		 * source and where to end. the last argument tells the service whether
		 * to loop the resource.
		 *
		 * \param id key under which the resource is stored in the collection.
		 * \param from starting point.
		 * \param to stops playback at this point.
		 *
		 * \note from and to playback has not been implemented yet!
		 */
		virtual void play( const string &id, u32 from, u32 to ) = 0;

		/*!
		 * \brief pauses the playback.
		 *
		 * pauses the playback of the given resource.
		 *
		 * \param id key under which the resource is stored in the collection.
		 */
		virtual void pause( const string &id ) = 0;

		/*!
		 * \brief stops the playback.
		 *
		 * stops the playback of the given resource.
		 *
		 * \param id key under which the resource is stored in the collection.
		 */
		virtual void stop( const string &id ) = 0;
	};
} /* Baukasten */

