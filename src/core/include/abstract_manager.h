#ifndef ABSTRACT_MANAGER_4A46G9D2
#define ABSTRACT_MANAGER_4A46G9D2

#include "global.h"
#include "state.h"

namespace Baukasten {
	using namespace std;

	template<class T>
	class AbstractManager {
	public:
		AbstractManager()
		{
		}

		virtual ~AbstractManager()
		{
		}

		virtual void add( T *t )
		{
			if ( t && !has( t->getId() ) )
				mMap[ t->getId() ] = t;
		}

		virtual T* get( const std::string &id ) const
		{
			typename map<string,T*>::const_iterator it = mMap.find( id );
			return ( it == mMap.end() ) ? 0 : it->second;
		}

		virtual map<string, T*> getAll() const
		{
			return mMap;
		}

		virtual bool has( const std::string &id ) const
		{
			return ( mMap.find( id ) != mMap.end() );
		}

		virtual void remove( const std::string &id )
		{
			mMap.erase( mMap.find( id ) );
		}

	protected:
		map<string, T*> mMap;
	};
} /* Baukasten */

#endif /* end of include guard: ABSTRACT_MANAGER_4A46G9D2 */
