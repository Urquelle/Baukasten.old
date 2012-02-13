#ifndef GENERIC_STATE_7VBP3DTZ
#define GENERIC_STATE_7VBP3DTZ

#include "model/GameEntity"
#include "model/Global"
#include "model/State"

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

		const T& value() const
		{
			if ( mIntState )
				return ( static_cast<GenericState<T>*>( mIntState ) )->value();

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
			GenericState<T> *newState = new GenericState<T>( id() );
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

		const T& value( const int i ) const
		{
			if ( mIntState )
				return ( static_cast<GenericState<vector<T>>*>( mIntState ) )->value( i );

			return mValues.at( i );
		}

		vector<T> values() const
		{
			return mValues;
		}

		void addValue( const T &value )
		{
			if ( mIntState )
				mIntState = 0;

			mValues.push_back( value );
			onChange().emit( this );
		}

		void setValue( const unsigned int i, const T &value )
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

		void setValues( vector<T> values )
		{
			if ( mIntState )
				mIntState = 0;
			mValues = values;
			onChange().emit( this );
		}

		void setValues( GenericState<vector<T>> *state )
		{
			mValues = state->values();
		}

		GenericState<vector<T>>* pack()
		{
			GenericState<vector<T>> *newState = new GenericState<vector<T>>( id() );
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
	typedef GenericState<vector<int>>		StateIntVector;
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
