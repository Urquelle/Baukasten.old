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
			GenericState( const std::string &id ) :
				State( id )
			{
			}

			GenericState( const std::string &id, T value ) :
				State( id ),
				mValue( value )
			{
			}

			~GenericState()
			{
			}

			const T& getValue() const
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

		// typedef some often used genericstates
		typedef GenericState<int>			StateInt;
		typedef GenericState<float>			StateFloat;
		typedef GenericState<std::string>	StateString;
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
