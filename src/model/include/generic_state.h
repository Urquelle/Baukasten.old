#ifndef GENERIC_STATE_7VBP3DTZ
#define GENERIC_STATE_7VBP3DTZ

#include "model/GameEntity"
#include "model/Global"
#include "model/State"

#include <vector>
#include <string>

namespace Baukasten {

	/*!
	 * \ingroup model
	 * @{
	 *
	 * \addtogroup state
	 *
	 * @{
	 *
	 * \class GenericState
	 * \brief generic state.
	 * \headerfile GenericState "model/GenericState"
	 *
	 * implements common methods for states with arbitrary value type.
	 */
	template<class T>
	class BAUKASTEN_EXPORT GenericState : public State {
	public:

		/*!
		 * \brief constructor.
		 * \param id State's id.
		 */
		GenericState( const string &id ) :
			State( id )
		{
		}

		/*!
		 * \brief constructor.
		 *
		 * additionaly to the object's id that is set in the constructor, a default
		 * value is set as well.
		 *
		 * \param id State's id.
		 * \param value initial value of the state.
		 */
		GenericState( const string &id, T value ) :
			State( id ),
			m_value( value )
		{
		}

		/*! destructor. */
		virtual ~GenericState()
		{
		}

		/*!
		 * \brief current value of the state.
		 * \return state's set value.
		 */
		T value() const
		{
			if ( m_intState )
				return ( static_cast<GenericState<T>*>( m_intState ) )->value();

			return m_value;
		}

		/*!
		 * \brief set state's value.
		 *
		 * sets the value of the state and emits the onChange() signal.
		 *
		 * \param value new value.
		 */
		void setValue( const T &value )
		{
			if ( m_intState )
				m_intState = 0;

			m_value = value;
			onChange().emit( this );
		}

		/*!
		 * \brief wrapper state.
		 *
		 * creates a new state object and sets its internal used
		 * state pointer to `this`.
		 *
		 * this is supposed to be used with EntityType object, which provides
		 * a pool of states to every GameEntity with this entity type. the idea behind
		 * this was to return the value of the entity type as long as the value
		 * of the state remains unchanged. as soon as an object writes to the
		 * shared state, a copy of this state is needed that can be written to, and
		 * that is assigned exclusivley to the object that wants to change the state.
		 *
		 * this way the shared state stays unchanged.
		 *
		 * however, in the current implementation, a copy of the state has to be made
		 * even if an object merely reads the value, due to the fact that it is possible
		 * to obtain the pointer to the state -- that would change as soon as we change the
		 * value --, hence holding an outdated pointer, instead of the newly created
		 * object with the new value. so by providing a new pointer on read operation we
		 * maintain the validity of the pointer right away even after the value has changed;
		 * losing the cache functionality though.
		 *
		 * \return pointer to a GenericState<T> object.
		 */
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
	/** @} */
	/** @} */

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
