#ifndef INC_OBJECTS_W8NDAGHK
#define INC_OBJECTS_W8NDAGHK

#include "global.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT ObjectsManager {
	public:
		ObjectsManager();
		virtual ~ObjectsManager();

		void addObject( const std::string&, void* );

		template<class T>
		T getObject( const std::string &id ) const
		{
			ObjectMap::const_iterator it = mObjects.find( id );
			return ( it == mObjects.end() )
				? 0
				: static_cast<T>( it->second );
		}

		bool hasObject( const std::string& ) const;
		void removeObject( const std::string& );

	private:
		ObjectMap	mObjects;
	};
} /* Baukasten */

#endif /* end of include guard: INC_OBJECTS_W8NDAGHK */
