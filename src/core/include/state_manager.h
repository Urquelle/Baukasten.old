#ifndef INC_STATES_18NEVRSZ
#define INC_STATES_18NEVRSZ

#include "global.h"

#include "abstract_manager.h"

namespace Baukasten {
	class State;

	class BAUKASTEN_EXPORT StateManager : protected AbstractManager<State> {
	public:
		StateManager();
		virtual ~StateManager();

		void addState( State* );
		void addState( const std::string&, State* );

		template<class T>
		T getState( const std::string &id ) const
		{
			return static_cast<T>( get( id ) );
		}

		StateMap getStates() const;
		bool hasState( const std::string& ) const;
	};
} /* Baukasten */

#endif /* end of include guard: INC_STATES_18NEVRSZ */

