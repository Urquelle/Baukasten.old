#ifndef INC_STATES_18NEVRSZ
#define INC_STATES_18NEVRSZ

#include "model/GenericManager"
#include "model/Global"

namespace Baukasten {
	class State;

	class BAUKASTEN_EXPORT StateManager :
		protected virtual GenericManager<State> {
	public:
		StateManager();
		virtual ~StateManager();

		void addState( State* );
		void addState( const std::string&, State* );

		template<class T>
		T state( const std::string &id ) const
		{
			return static_cast<T>( get( id ) );
		}

		TMap states() const;
		bool hasState( const std::string& ) const;
	};
} /* Baukasten */

#endif /* end of include guard: INC_STATES_18NEVRSZ */

