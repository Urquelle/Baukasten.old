#pragma once

#include "services/Global"

namespace Baukasten {
	class IAudio;
	class IGraphics;
	class IInput;

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup interface
	 * @{
	 *
	 * \class Services
	 * \brief provides the interface to the core services.
	 * \headerfile Services "services/Services"
	 *
	 * provides methods to retrieve the objects that implement
	 * the IAudio, IInput and IGraphics interfaces.
	 */
	class BAUKASTEN_EXPORT Services {
	public:

		/*!
		 * \brief singleton method.
		 *
		 * singleton method to retrieve an instance of Services object.
		 *
		 * \return pointer to a static Services object.
		 */
		static Services& instance();

		/*! destructor */
		virtual ~Services();

		/*!
		 * \brief initialisation method.
		 *
		 * calls the init() method of all services.
		 *
		 * \param argc number of command line arguments.
		 * \param argv an array of command line argument.
		 */
		void init( int, char** );

		/*!
		 * \brief shutdown method.
		 *
		 * calls the shutdown() method of all services.
		 */
		void shutdown();

		/*!
		 * \brief provides access to the audio interface.
		 *
		 * returns an object that provides the implementation of the
		 * IAudio interface.
		 *
		 * \return pointer to IAudio object.
		 */
		IAudio&     audioService() const;

		/*!
		 * \brief provides access to the input interface.
		 *
		 * returns an object that provides the implementation of the
		 * IInput interface.
		 *
		 * \return pointer to IInput object.
		 */
		IInput&     inputService() const;

		/*!
		 * \brief provides access to the graphics interface.
		 *
		 * returns an object that provides the implementation of the
		 * IGraphics interface.
		 *
		 * \return pointer to IGraphics object.
		 */
		IGraphics&  graphicsService() const;

		/*!
		 * \brief get the number of command line arguments.
		 * \return int number of command line arguments provided.
		 */
		int         argc();

		/*!
		 * \brief get the number of command line arguments.
		 * \return int number of command line arguments provided.
		 */
		char**      argv() const;

	private:
		Services();
		Services( const Services& );
		Services& operator=( const Services& );

		IAudio*     m_audio;
		IGraphics*  m_graphics;
		IInput*     m_input;
		int         m_argc;
		char**      m_argv;
	};
	/** @} */
	/** @} */
} /* Baukasten */

