#ifndef GENERIC_MANAGER_4A46G9D2
#define GENERIC_MANAGER_4A46G9D2

#include "core/Assert"
#include "core/Debug"
#include "model/Action"
#include "model/Global"
#include "model/State"

namespace Baukasten {

	/*!
	 * \ingroup model
	 * @{
	 *
	 * \addtogroup manager
	 * @{
	 *
	 * \class GenericManager
	 * \brief implementation of a container class.
	 * \headerfile GenericManager "model/GenericManager"
	 *
	 * implements a container with arbitrary object type.
	 * adds methods to act upon the collection.
	 *
	 * \tparam T class to use as second parameter of the map.
	 */
	template<class T>
	class BAUKASTEN_EXPORT GenericManager {
	public:
		typedef map<string, shared_ptr<T> > TMap;

		/*!
		 * constructor
		 *
		 * nothing fancy here.
		 */
		GenericManager()
		{
		}

		/*! destructor */
		virtual ~GenericManager()
		{
		}

		/*!
		 * \brief add object t to the collection.
		 *
		 * \see add( const string&, T* )
		 * \param t an object to add to the map.
		 */
		virtual void add( T *t )
		{
			BK_ASSERT( t != 0, "t must not be 0." );
			add( t->id(), t );
		}

		/*!
		 * \brief add object t to the collection.
		 *
		 * adds object t to the object map if t is a valid pointer
		 * and if id isn't already taken by another object.
		 *
		 * \param id id for the object in the map
		 * \param t object to be added to the map
		 */
		virtual void add( const string &id, T *t )
		{
			BK_ASSERT( t != 0, "t must not be 0." );
			BK_ASSERT( !has( id ), "id " << id << " must be unique in the collection." );

			m_map[ id ] = shared_ptr<T>( t );
		}

		/*!
		 * \brief fetch an object from the map.
		 *
		 * fetch an object with the given id from the collection.
		 *
		 * \param id id under which the object is stored in the map.
		 * \return object of type T* if object is found, 0 if the object
		 * is not in the map.
		 */
		virtual T* get( const string &id ) const
		{
			typename TMap::const_iterator it = m_map.find( id );

			if ( it == m_map.end() )
				return 0;

			return it->second.get();
		}

		/*!
		 * \brief fetch all objects from the map.
		 *
		 * returns the map with all the objects.
		 *
		 * \return map of object pointers of type T.
		 */
		virtual TMap all() const
		{
			return m_map;
		}

		/*!
		 * \brief query whether the map contains the id.
		 *
		 * queries the map whether there's an entry to the
		 * given id.
		 *
		 * \param id id under which the object is stored in the map.
		 * \return returns true if the key id is in the map, false otherwise.
		 */
		virtual bool has( const string &id ) const
		{
			return m_map.count( id ) > 0;
		}

		/*!
		 * \brief remove the object to the given id.
		 *
		 * removes the object from the map. basically it calls
		 * the erase function on the map.
		 *
		 * \param id id string for the key in the map.
		 */
		virtual void remove( const string &id )
		{
			m_map.erase( m_map.find( id ) );
		}

	protected:
		TMap m_map;
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: GENERIC_MANAGER_4A46G9D2 */

