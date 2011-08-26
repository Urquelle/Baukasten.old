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
			return mValue;
		}

		void setValue( const T &value )
		{
			if ( mIsLocked ) {
				GameEntity *entity = 0;

				/* go through all entities in the list which registered themself
				 * to have returned the state from their type object, so in case
				 * the value of this state's is changed a new state has to be
				 * instantiated and assigned directly to the entity, so that the
				 * value of the type object isn't overwritten.
				 */
				while ( mEntities.size() ) {

					/* have to cast the const away, since the getState() method is
					 * const, and that's where the addTo() method is used to provide
					 * the state with the object the state is to add to. addTo() method
					 * is supplied with this pointer as parameter, the getState() method
					 * is const, hence this pointer is const.
					 */
					entity = const_cast<GameEntity*>( mEntities.front() );
					entity->addState( new GenericState<T>( getId(), value ) );

					// remove entity from the registered list again.
					mEntities.pop_front();
				}

				// unlock the state, as all requests have been dealed with.
				mIsLocked = false;
			} else {
				mValue = value;
			}
		}

	private:
		T						mValue;
	};

	// typedef some often used genericstates
	typedef GenericState<int>			StateInt;
	typedef GenericState<float>			StateFloat;
	typedef GenericState<std::string>	StateString;
	typedef GenericState<bool>			StateBool;
} /* Baukasten */

#endif /* end of include guard: GENERIC_STATE_7VBP3DTZ */
