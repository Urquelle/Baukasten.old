#ifndef ABSTRACT_MANAGER_4A46G9D2
#define ABSTRACT_MANAGER_4A46G9D2

#include "global.h"
#include "action.h"
#include "state.h"

namespace Baukasten {
	using namespace std;

	/*! \defgroup manager Manager Classes */

	/*! \brief implementation of a container class.
	 *
	 * \ingroup manager
	 *
	 * implements a container with arbitrary object type.
	 * adds methods to act upon the collection.
	 *
	 * \tparam T class to use as second parameter of the map.
	 */
	template<class T>
	class AbstractManager {
	public:
		/*! constructor
		 *
		 * nothing fancy here.
		 */
		AbstractManager()
		{
		}

		/*! destructor */
		virtual ~AbstractManager()
		{
			typename map<string, T*>::iterator it = mMap.begin();
			while ( it != mMap.end() ) {
				if ( (*it).second )
					delete (*it).second;
				++it;
			}
		}

		/*! \brief add object t to the collection.
		 *
		 * \see add( const std::string&, T* )
		 * \param t an object to add to the map.
		 */
		virtual void add( T *t )
		{
			if ( t )
				add( t->getId(), t );
		}

		/*! \brief add object t to the collection.
		 *
		 * adds object t to the object map if t is a valid pointer
		 * and if id isn't already taken by another object.
		 *
		 * \param id id for the object in the map
		 * \param t object to be added to the map
		 */
		virtual void add( const std::string &id, T *t )
		{
			if ( t && !has( id ) )
				mMap[ id ] = t;
		}

		/*! \brief fetch an object from the map.
		 *
		 * fetch an object with the given id from the collection.
		 *
		 * \param id id under which the object is stored in the map.
		 * \return object of type T* if object is found, 0 if the object
		 * is not in the map.
		 */
		virtual T* get( const std::string &id ) const
		{
			typename map<string,T*>::const_iterator it = mMap.find( id );
			return ( it == mMap.end() ) ? 0 : it->second;
		}

		/*! \brief fetch all objects from the map.
		 *
		 * returns the map with all the objects.
		 *
		 * \return map of object pointers of type T.
		 */
		virtual map<string, T*> getAll() const
		{
			return mMap;
		}

		/*! \brief query whether the map contains the id.
		 *
		 * queries the map whether there's an entry to the
		 * given id.
		 *
		 * \param id id under which the object is stored in the map.
		 * \return returns true if the key id is in the map, false otherwise.
		 */
		virtual bool has( const std::string &id ) const
		{
			return ( mMap.find( id ) != mMap.end() );
		}

		/*! \brief remove the object to the given id.
		 *
		 * removes the object from the map. basically it calls
		 * the erase function on the map.
		 *
		 * \param id id string for the key in the map.
		 */
		virtual void remove( const std::string &id )
		{
			mMap.erase( mMap.find( id ) );
		}

	protected:
		map<string, T*> mMap;
	};
} /* Baukasten */

#endif /* end of include guard: ABSTRACT_MANAGER_4A46G9D2 */
