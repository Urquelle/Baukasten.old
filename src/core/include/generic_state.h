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
			GenericState( Entity &parent ) :
				State( parent )
			{
			}

			GenericState( Entity &parent, const std::string &id ) :
				State( parent, id )
			{
			}

			~GenericState()
			{
			}

			const T getValue() const
			{
				return mValue;
			}

			void setValue( const T &value )
			{
				mValue = value;
			}

		private:
			T mValue;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
