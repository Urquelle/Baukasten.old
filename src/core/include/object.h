#ifndef OBJECT_3MNIVLWP
#define OBJECT_3MNIVLWP

#include "global.h"

namespace Baukasten {
	namespace Core {
		class BAUKASTEN_EXPORT Object {
		public:
			Object( const std::string& );
			virtual ~Object();

			void operator=( const Object& );
			bool operator==( const Object& ) const;

			const std::string getId() const;

		private:
			std::string	mId;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: OBJECT_3MNIVLWP */
