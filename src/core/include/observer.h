#ifndef OBSERVER_DJMNQ12W
#define OBSERVER_DJMNQ12W

#include "global.h"

#include <sigc++/sigc++.h>

#include <map>
#include <string>

namespace Baukasten {

	using namespace std;
	using namespace sigc;

	typedef map<string, signal<void>*> SignalMap;

	class BAUKASTEN_EXPORT Observer {
	public:

		static Observer* instance();
		virtual ~Observer();

		template<typename ReturnType, typename Params>
		signal<ReturnType, Params>* get( const string &id )
		{
			SignalMap::const_iterator it = mSignals.find( id );
			if ( it == mSignals.end() )
				return 0;

			return reinterpret_cast<signal<ReturnType, Params>*>( it->second );
		}

		template<typename ReturnType, typename Params>
		bool registerSignal( const string &id )
		{
			SignalMap::const_iterator it = mSignals.find( id );
			if ( it != mSignals.end() ) {
				// signal with the given id's already registered
				return false;
			}

			// create a new signal instance here
			signal<ReturnType, Params> *sig = new signal<ReturnType, Params>();
			mSignals[ id ] = reinterpret_cast<signal<void>*>(sig);

			return true;
		}

	private:
		Observer();

		SignalMap			mSignals;
		static Observer*	mInstance;
	};
} /* Baukasten */

#endif /* end of include guard: OBSERVER_DJMNQ12W */
