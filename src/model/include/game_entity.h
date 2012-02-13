#ifndef GAME_ENTITY_W1MJLLNE
#define GAME_ENTITY_W1MJLLNE

#include "model/ActionManager"
#include "model/Entity"
#include "model/EntityType"
#include "model/Global"
#include "model/StateManager"

#include <sigc++/sigc++.h>

namespace Baukasten {
	class EntityType;
	class Form;

	typedef sigc::signal<void, GameEntity*, State*> StateSignal;
	typedef sigc::signal<void, GameEntity*, Action*> ActionSignal;

	class BAUKASTEN_EXPORT GameEntity : public Entity,
		public ActionManager, public StateManager {
	public:

		GameEntity( const std::string& );
		GameEntity( const GameEntity& );
		virtual ~GameEntity();

		void setType( EntityType* );
		EntityType* type() const;

		void setForm( Form* );
		Form* form() const;

		void addState( State* );
		void addState( const std::string&, State* );
		bool hasState( const std::string& ) const;

		template<class T>
		T state( const std::string &id )
		{
			T state = StateManager::state<T>( id );

			if ( !state && type() ) {
				state = type()->state<T>( id );

				if ( state ) {
					state = state->pack();
					addState( state );
				}
			}

			return state;
		}

		void addChild( GameEntity* );
		GameEntity* child( const std::string& ) const;
		GameEntityMap children() const;
		void removeChild( const std::string& );

		void setParent( GameEntity* );
		GameEntity* parent() const;

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

