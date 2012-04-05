#pragma once

#include "services/Global"

namespace Baukasten {
	class Services;

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup interface
	 * @{
	 *
	 * \class IService
	 * \brief service interface declaration.
	 * \headerfile IService "services/IService"
	 *
	 * declares the methods that an interface class has to define, and
	 * provides a common implementation for a couple of the methods.
	 */
	class BAUKASTEN_EXPORT IService {
	public:

		/*!
		 * \brief constructor.
		 *
		 * initialises private variables, that are needed in the default
		 * implementation of methods.
		 *
		 * \param name name of the service.
		 */
		IService( const string &name ) :
			m_ready( false ),
			m_name( name )
		{
		}

		/*!
		 * \brief method to init the service.
		 *
		 * in order for being able to use a service, it has -- in some
		 * cases -- to be initalised before. this method provides the place
		 * to do this.
		 *
		 * \param services pointer to Services object.
		 */
		virtual void init( Services *services ) = 0;

		/*!
		 * \brief method to shutdown the service.
		 *
		 * everything that is needed to clean up the service, should go in
		 * this method.
		 */
		virtual void shutdown() = 0;

		/*!
		 * \brief setter for the ready attribute.
		 *
		 * sets the value of the ready attribute of a service, which indicates
		 * whether the service is ready to be used.
		 *
		 * \sa isReady()
		 * \param ready bool value.
		 */
		virtual void setIsReady( bool ready ) { m_ready = ready; }

		/*!
		 * \brief getter method for the ready attribute.
		 *
		 * tells the caller whether the service is ready to be used.
		 *
		 * \return boolean of the ready attribute.
		 */
		virtual bool isReady() const { return m_ready; }

		/*!
		 * \brief getter method for the name attribute.
		 *
		 * \return the given name of the service.
		 */
		virtual string name() const { return m_name; }

	private:
		bool m_ready;
		string m_name;
	};
	/** @} */
	/** @} */
}

