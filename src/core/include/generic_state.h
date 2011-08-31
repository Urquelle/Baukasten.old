#ifndef GENERIC_STATE_7VBP3DTZ
#define GENERIC_STATE_7VBP3DTZ

#include "global.h"

#include "game_entity.h"
#include "state.h"

#include <iostream>
#include <list>
#include <string>

namespace Baukasten {
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
			if ( mIntState )
				return ( static_cast<GenericState<T>*>( mIntState ) )->getValue();

			return mValue;
		}

		void setValue( const T &value )
		{
			if ( mIntState )
				mIntState = 0;

			mValue = value;
			onChange().emit( this );
		}

		GenericState<T>* pack()
		{
			GenericState<T> *newState = new GenericState<T>( getId() );
			newState->mIntState = this;
			return newState;
		}

	private:
		T mValue;
	};

	// typedef some often used genericstates
	typedef GenericState<int>			StateInt;
	typedef GenericState<float>			StateFloat;
	typedef GenericState<std::string>	StateString;
	typedef GenericState<bool>			StateBool;
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
