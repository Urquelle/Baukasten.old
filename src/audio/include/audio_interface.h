#ifndef AUDIO_INTERFACE_H_21IELBUV
#define AUDIO_INTERFACE_H_21IELBUV

#include "audio/Global"

namespace Baukasten {
	class IAudio;

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup audio
	 * @{
	 *
	 * \class AudioInterface
	 * \brief audio interface class.
	 * \headerfile AudioInterface "audio/AudioInterface"
	 *
	 * the class provides the interface to retrieve an object
	 * implementing the IAudio interface.
	 */
	class BAUKASTEN_EXPORT AudioInterface {
	public:

		/*!
		 * \brief singleton method to retrieve implementation.
		 *
		 * singleton method which provides the interface to retrieve
		 * the object implementing the IAudio interface.
		 *
		 * \return pointer to an IAudio object.
		 */
		static IAudio* instance();

	private:
		AudioInterface() {}

		static IAudio* m_instance;
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: AUDIO_INTERFACE_H_21IELBUV */

