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

		virtual ~GenericState()
		{
		}

		T value() const
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

	template<template<class, class> class V, class T>
	class BAUKASTEN_EXPORT GenericStateCollection : public State {
		typedef V<T, allocator<T> > Container;
		typedef GenericStateCollection<V,T> ThisType;
	public:

		GenericStateCollection( const string &id ) :
			State( id )
		{
		}

		GenericStateCollection( const string &id, Container values ) :
			State( id ),
			m_values( values )
		{
		}

		virtual ~GenericStateCollection()
		{
		}

		T value( const s32 i ) const
		{
			if ( m_intState )
				return ( static_cast<ThisType*>( m_intState ) )->value( i );

			return m_values.at( i );
		}

		Container values() const
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

		void setValue( const s32 i, const T &value )
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

		void setValues( Container values )
		{
			if ( m_intState )
				m_intState = 0;
			m_values = values;
			onChange().emit( this );
		}

		void setValues( ThisType *state )
		{
			m_values = state->values();
		}

		ThisType* pack()
		{
			ThisType *newState = new ThisType( id() );
			newState->m_intState = this;
			return newState;
		}

	private:
		V<T, allocator<T> > m_values;
	};

	// typedef some often used genericstates
	typedef  GenericState<s32>                      StateInt;
	typedef  GenericState<float>                    StateFloat;
	typedef  GenericState<string>                   StateString;
	typedef  GenericState<bool>                     StateBool;
	typedef  GenericStateCollection<vector,string>  StateStringVector;
	typedef  GenericStateCollection<vector,int>     StateIntVector;
	typedef  GenericStateCollection<vector,float>   StateFloatVector;
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
