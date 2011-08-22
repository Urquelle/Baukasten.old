#ifndef INC_OBJECTS_W8NDAGHK
#define INC_OBJECTS_W8NDAGHK

#include "global.h"

namespace Baukasten {
	namespace Core {
		class BAUKASTEN_EXPORT IncObjects {
		public:
			IncObjects();
			virtual ~IncObjects();

			void addObject( void*, const std::string& );
			void* getObject( const std::string& ) const;
			bool hasObject( const std::string& ) const;
			void removeObject( const std::string& );

		private:
			ObjectMap	mObjects;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: INC_OBJECTS_W8NDAGHK */
