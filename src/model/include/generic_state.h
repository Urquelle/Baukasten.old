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

		GenericState( const string &id ) :
			State( id )
		{
		}

		GenericState( const string &id, T value ) :
			State( id ),
			m_value( value )
		{
		}

		~GenericState()
		{
		}

		const T& value() const
		{
			if ( m_intState )
				return ( static_cast<GenericState<T>*>( m_intState ) )->value();

			return m_value;
		}

		void setValue( const T &value )
		{
			if ( m_intState )
				m_intState = 0;

			m_value = value;
			onChange().emit( this );
		}

		GenericState<T>* pack()
		{
			GenericState<T> *newState = new GenericState<T>( id() );
			newState->m_intState = this;
			return newState;
		}

	private:
		T m_value;
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
			m_values( values )
		{
		}

		~GenericState()
		{
		}

		const T& value( const int i ) const
		{
			if ( m_intState )
				return ( static_cast<GenericState<vector<T>>*>( m_intState ) )->value( i );

			return m_values.at( i );
		}

		vector<T> values() const
		{
			return m_values;
		}

		void addValue( const T &value )
		{
			if ( m_intState )
				m_intState = 0;

			m_values.push_back( value );
			onChange().emit( this );
		}

		void setValue( const unsigned int i, const T &value )
		{
			if ( m_intState )
				m_intState = 0;

			BK_ASSERT(
				i < m_values.size(),
				"position to include the value must not be greater than collection's size"
			);

			m_values[i] = value;
			onChange().emit( this );
		}

		void setValues( vector<T> values )
		{
			if ( m_intState )
				m_intState = 0;
			m_values = values;
			onChange().emit( this );
		}

		void setValues( GenericState<vector<T>> *state )
		{
			m_values = state->values();
		}

		GenericState<vector<T>>* pack()
		{
			GenericState<vector<T>> *newState = new GenericState<vector<T>>( id() );
			newState->m_intState = this;
			return newState;
		}

	private:
		vector<T> m_values;
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
