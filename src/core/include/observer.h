#ifndef OBSERVER_DJMNQ12W
#define OBSERVER_DJMNQ12W

#include <sigc++/sigc++.h>

#include <map>
#include <string>

namespace Baukasten {

	typedef map<std::string, sigc::signal<void>*> SignalMap;

	class BAUKASTEN_EXPORT Observer {
	public:

		static Observer* instance()
		{
			if ( !mInstance )
				mInstance = new Observer();
			return mInstance;
		}

		virtual ~Observer() {}

		template<typename ReturnType, typename Params>
		sigc::signal<ReturnType, Params>* get( const std::string &id )
		{
			SignalMap::const_iterator it = mSignals.find( id );
			if ( it == mSignals.end() )
				return 0;

			return reinterpret_cast<sigc::signal<ReturnType, Params>*>( it->second );
		}

		template<typename ReturnType, typename Params>
		bool registerSignal( const std::string &id )
		{
			SignalMap::const_iterator it = mSignals.find( id );
			if ( it != mSignals.end() ) {
				// signal with the given id's already registered
				return false;
			}

			// create a new signal instance here
			sigc::signal<ReturnType, Params> *sig = new sigc::signal<ReturnType, Params>();
			mSignals[ id ] = reinterpret_cast<sigc::signal<void>*>(sig);

			return true;
		}

	private:
		Observer()
		{
		}

		SignalMap			mSignals;
		static Observer*	mInstance;
	};

	Observer* Observer::mInstance = 0;
} /* Baukasten */

#endif /* end of include guard: OBSERVER_DJMNQ12W */
