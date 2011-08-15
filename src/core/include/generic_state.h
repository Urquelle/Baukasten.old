#ifndef GENERIC_STATE_7VBP3DTZ
#define GENERIC_STATE_7VBP3DTZ

#include "global.h"
#include "state.h"

#include <string>

namespace Baukasten {
	namespace Core {
		template<class T>
		class BAUKASTEN_EXPORT GenericState : public State {
		public:
			GenericState( Entity& );
			GenericState( Entity&, const std::string& );

			~GenericState();

			const T getValue() const;
			void setValue( const T& );

		private:
			T mValue;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
