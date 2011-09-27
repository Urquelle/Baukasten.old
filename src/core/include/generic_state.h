#ifndef GENERIC_STATE_7VBP3DTZ
#define GENERIC_STATE_7VBP3DTZ

#include "global.h"

#include "game_entity.h"
#include "state.h"

#include <vector>
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

	template<class T>
	class BAUKASTEN_EXPORT GenericState<vector<T>> : public State {
	public:

		GenericState( const string &id ) :
			State( id )
		{
		}

		GenericState( const string &id, vector<T> values ) :
			State( id ),
			mValues( values )
		{
		}

		~GenericState()
		{
		}

		const T& getValue( const int i ) const
		{
			if ( mIntState )
				return ( static_cast<GenericState<T>*>( mIntState ) )->getValue( i );

			return mValues.at( i );
		}

		void addValue( const T &value )
		{
			if ( mIntState )
				mIntState = 0;

			mValues.push_back( value );
			onChange().emit( this );
		}

		void setValue( const int i, const T &value )
		{
			if ( mIntState )
				mIntState = 0;

			BK_ASSERT(
				i < mValues.size(),
				"position to include the value must not be greater than collection's size"
			);

			mValues[i] = value;
			onChange().emit( this );
		}

		GenericState<vector<T>>* pack()
		{
			GenericState<vector<T>> *newState = new GenericState<vector<T>>( getId() );
			newState->mIntState = this;
			return newState;
		}

	private:
		std::vector<T> mValues;
	};

	// typedef some often used genericstates
	typedef GenericState<int>				StateInt;
	typedef GenericState<float>				StateFloat;
	typedef GenericState<string>			StateString;
	typedef GenericState<bool>				StateBool;
	typedef GenericState<vector<string>>	StateStringVector;
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
