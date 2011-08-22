#ifndef INC_STATES_18NEVRSZ
#define INC_STATES_18NEVRSZ

#include "global.h"

#include "abstract_manager.h"

namespace Baukasten {
	namespace Core {
		class State;

		class BAUKASTEN_EXPORT StatesManager : public AbstractManager<State> {
		public:
			StatesManager();
			virtual ~StatesManager();

            void addState( State* );
            State* getState( const std::string& ) const;
			StateMap getStates() const;
            bool hasState( const std::string& ) const;
		};
	} /* Core */
} /* Baukasten */

#endif /* end of include guard: INC_STATES_18NEVRSZ */

