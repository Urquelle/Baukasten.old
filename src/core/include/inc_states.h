#ifndef INC_STATES_18NEVRSZ
#define INC_STATES_18NEVRSZ

#include "global.h"

namespace Baukasten {
	namespace Core {
		class State;

		class BAUKASTEN_EXPORT IncStates {
		public:
			IncStates();
			virtual ~IncStates();

            void addState( State* );
            State* getState( const std::string& ) const;
			StateMap getStates() const;
            bool hasState( const std::string& ) const;

		private:
			StateMap mStates;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: INC_STATES_18NEVRSZ */

