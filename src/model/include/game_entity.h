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

	/*!
	 * \brief represents an abstract entity that is a part of a game.
	 *
	 * \ingroup model entity
	 *
	 * \headerfile GameEntity "model/GameEntity"
	 *
	 * this class is the container which is meant to
	 * represent *any* given entity in a game/application. initially an
	 * anonymous, empty and dumb object, it can be built -- through
	 * decorating -- to represent the wanted entity.
	 *
	 * decoration, in this case, means you add State and Action objects
	 * to the GameEntity, that represent any attribute of your desired
	 * entity (e. g. hitpoints, level, gender, ...).
	 */
	class BAUKASTEN_EXPORT GameEntity : public Entity,
		public ActionManager, public StateManager {
	public:

		/*!
		 * \brief constructor
		 *
		 * \param id id of the new object.
		 */
		GameEntity( const string& );

		/*!
		 * \brief copy constructor
		 *
		 * \param rhs GameEntity object.
		 */
		GameEntity( const GameEntity& );

		/*! \brief destructor */
		virtual ~GameEntity();

		/*!
		 * \brief set the type of the entity.
		 *
		 * sets the type of an entity. any previously set type is
		 * overwritten.
		 *
		 * \param type GameType object.
		 */
		void setType( EntityType* );

		/*!
		 * \brief adds a type to the chain of types.
		 *
		 * adds a type to the chain of already set types. becomes
		 * the primary type of the entity.
		 *
		 * if a type X was already set, X becomes the parent type
		 * of the given type.
		 *
		 * \param type GameType object.
		 */
		void addType( EntityType* );

		/*!
		 * \brief get the main type.
		 *
		 * returns the main type of the entity.
		 *
		 * \return EntityType object if set, 0 otherwise.
		 */
		EntityType* type() const;

		/*!
		 * \brief set form of the entity.
		 *
		 * sets the graphical representation object of the entity.
		 *
		 * \param form Form object.
		 */
		void setForm( Form* );

		/*!
		 * \brief get the form object.
		 *
		 * returns the graphical representation object of the entity.
		 *
		 * \return Form object instance.
		 */
		Form* form() const;

		/*!
		 * \brief adds a state to the entity.
		 *
		 * decoration method meant to add attributes, represented by
		 * State, to the entity.
		 *
		 * convenience method, which takes State::id() and calls
		 * addState( const string&, State* ) method with the id as the
		 * first argument and the given state as the second.
		 *
		 * \param state
		 * \sa addState( const string&, State* )
		 */
		void addState( State* );

		/*!
		 * \brief adds a state to the entity.
		 *
		 * decoration method meant to add attributes, represented by
		 * State, to the entity.
		 *
		 * puts the given state to the collection using the id as the
		 * key.
		 *
		 * \note id has to be unique in the entity's collection of states.
		 * \warning if the id is already present in the collection, the
		 * application exits with a warning.
		 */
		void addState( const string&, State* );

		/*!
		 * \brief check if a state is present.
		 *
		 * queries the entitie's collection for presence of a state stored
		 * under the given id.
		 *
		 * if state is not present in the GameEntity object itself, its EntityType
		 * objects are queried for presence of the state.
		 *
		 * \param id key under which the state is stored.
		 * \return true if state is present, false otherwise.
		 */
		bool hasState( const string& ) const;

		/*!
		 * \brief get a state to the id.
		 *
		 * get a State object to the given id. if no entry in the collection is
		 * found in the entities collection of states, its chain of EntityType
		 * objects is queried for the state with the id.
		 *
		 * upon fetching the state is converted to the type of given template
		 * argument T.
		 *
		 * \param id key under which the state object is stored.
		 * \tparam T type of the wanted state object.
		 * \return State object if found, 0 otherwise.
		 */
		template<class T>
		T state( const string &id )
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

		/*!
		 * \brief add child entity to the entity object.
		 *
		 * an entity may contain 0 or n child entities, which in turn can
		 * contain 0 or m child entities. entities in this collection are
		 * considered inactive as long as they are not present either in
		 * the virtual space or logical space of entities form object.
		 *
		 * this collection is usefull to keep track of all child objects that
		 * are needed for entity to operate.
		 *
		 * a car object, for instance, would contain all its parts as child
		 * objects and push them into the virtual space for them to be drawn
		 * and into the logical space for them to take action.
		 *
		 * this is a convenience method, which in turn calls addChild() with
		 * the given child's id as the first argument and the child as the second.
		 *
		 * \param child GameEntity object.
		 * \note child id has to be unique in the children collection.
		 */
		void addChild( GameEntity* );

		/*!
		 * \brief add child entity to the entity object.
		 *
		 * an entity may contain 0 or n child entities, which in turn can
		 * contain 0 or m child entities. entities in this collection are
		 * considered inactive as long as they are not present either in
		 * the virtual space or logical space of entities form object.
		 *
		 * this collection is usefull to keep track of all child objects that
		 * are needed for entity to operate.
		 *
		 * a car object, for instance, would contain all its parts as child
		 * objects and push them into the virtual space for them to be drawn
		 * and into the logical space for them to take action.
		 *
		 * \param id key under which the object is stored.
		 * \param child GameEntity object.
		 * \note child id has to be unique in the children collection.
		 */
		void addChild( const string&, GameEntity* );

		/*!
		 * \brief fetch a child GameEntity.
		 *
		 * fetch a child GameEntity which is stored under the given
		 * id in the collection.
		 *
		 * \param id key under which the child is stored.
		 * \return pointer to GameEntity if found, 0 otherwise.
		 */
		GameEntity* child( const string& ) const;

		/*!
		 * \brief fetch the whole children collection.
		 *
		 * fetch a map of all stored children.
		 *
		 * \return map of GameEntity pointers.
		 */
		GameEntityMap children() const;

		/*!
		 * \brief remove a child entity.
		 *
		 * removes a child from the child collection.
		 *
		 * \note the child object's destructor is called after the
		 * child object is removed from the collection.
		 */
		void removeChild( const string& );

		/*!
		 * \brief set parent object.
		 *
		 * sets the parent object of the entity.
		 *
		 * \param parent pointer of GameEntity object.
		 * \note doesn't add the entity to parent's children collection.
		 */
		void setParent( GameEntity* );

		/*!
		 * \brief get the parent object.
		 *
		 * \return pointer of GameEntity object.
		 */
		GameEntity* parent() const;

		/*!
		 * \brief runs all invoked actions.
		 *
		 * runs all invoked actions of the entity and all
		 * child entities in the logical space.
		 *
		 * \sa Form
		 * \sa LogicalSpace
		 */
		virtual void runActions();

		/*!
		 * \brief get the StateSignal object.
		 *
		 * \return reference to the StateSignal object.
		 */
		StateSignal& onStateChanged();

		/*!
		 * \brief get the ActionSignal object.
		 *
		 * returns the signal object that emits a signal after an action is
		 * invoked.
		 *
		 * \return ActionSignal object.
		 */
		ActionSignal& onActionInvoked();

		/*!
		 * \brief get the ActionSignal object.
		 *
		 * returns the signal object that emits a signal after an action
		 * is run.
		 *
		 * \return ActionSignal object.
		 */
		ActionSignal& onActionRun();

	private:
		void stateChanged( State* );

		EntityType*			m_type;
		shared_ptr<Form>	m_form;
		GameEntityMap		m_children;
		GameEntity*			m_parent;

		// signals
		StateSignal		m_stateChanged;
		ActionSignal	m_actionInvoked;
		ActionSignal	m_actionRun;
	};
} /* Baukasten */

#endif /* end of include guard: GAME_ENTITY_W1MJLLNE */

