#ifndef GAME_ENTITY_W1MJLLNE
#define GAME_ENTITY_W1MJLLNE

#include "global.h"

#include "action_manager.h"
#include "entity.h"
#include "entity_type.h"
#include "state_manager.h"

#include <sigc++/sigc++.h>

namespace Baukasten {
	class EntityType;
	class Form;

	typedef sigc::signal<void, GameEntity*, State*> StateSignal;
	typedef sigc::signal<void, GameEntity*, Action*> ActionSignal;

	class BAUKASTEN_EXPORT GameEntity : public Entity,
		public ActionManager, public StateManager {
	public:
		friend class State;

		GameEntity( const std::string& );
		GameEntity( const GameEntity& );
		virtual ~GameEntity();

		void setType( EntityType* );
		EntityType* getType() const;

		void setForm( Form* );
		Form* getForm() const;

		void addState( State* );
		void addState( const std::string&, State* );
		bool hasState( const std::string& ) const;

		template<class T>
		T getState( const std::string &id )
		{
			T state = StateManager::getState<T>( id );

			if ( !state && getType() ) {
				state = getType()->getState<T>( id );

				if ( state ) {
					state = state->pack();
					addState( state );
				}
			}

			return state;
		}

		void addChild( GameEntity* );
		GameEntity* getChild( const std::string& ) const;
		GameEntityMap getChildren() const;
		void removeChild( const std::string& );

		void setParent( GameEntity* );
		GameEntity* getParent() const;

		virtual void runActions();

		StateSignal& onStateChanged();
		ActionSignal& onActionInvoked();
		ActionSignal& onActionRun();

	private:
		void stateChanged( State* );

		EntityType*			mType;
		shared_ptr<Form>	mForm;
		GameEntityMap		mChildren;
		GameEntity*			mParent;

		// signals
		StateSignal		mStateChanged;
		ActionSignal	mActionInvoked;
		ActionSignal	mActionRun;
	};
} /* Baukasten */

#endif /* end of include guard: GAME_ENTITY_W1MJLLNE */

