#ifndef ENTITY_TYPE_XJ90PEI
#define ENTITY_TYPE_XJ90PEI

#include "model/Entity"
#include "model/Global"
#include "model/StateManager"

namespace Baukasten {
	/*!
	 * \brief base class in the model module.
	 *
	 * \ingroup model entity
	 *
	 * \headerfile EntityType "model/EntityType"
	 *
	 * represents an abstraction of what an entity can be. consists of state and
	 * (not yet) action objects. doesn't use the objects itself though, only
	 * provides an access to those objects to game entities having this type.
	 */
	class BAUKASTEN_EXPORT EntityType :
		public Entity, public StateManager {
	public:

		/*!
		 * \brief constructor
		 *
		 * basic constructor.
		 *
		 * \param id id of the EntityType object.
		 */
		EntityType( const string& );

		/*! \brief destructor */
		virtual ~EntityType();

		/*!
		 * \brief set parent of the entitytype
		 *
		 * as the entity types can build a chain of types, this
		 * function provides the functionallity to set the parent
		 * type.
		 *
		 * \param parent parent EntityType object.
		 */
		void setParent( EntityType* );

		/*!
		 * \brief get the parent EntityType object.
		 *
		 * returns the parent EntityType object of this type, if present.
		 *
		 * \return EntityType if a parent is set, 0 otherwise.
		 */
		EntityType* parent() const;

		/*!
		 * \brief add a child to the entity type chain.
		 *
		 * adds a child EntityType object to the entity type
		 * chain.
		 *
		 * \param child EntityType object.
		 */
		void addChild( EntityType* );

		/*!
		 * \brief remove a child from the type chain.
		 *
		 * removes the given EntityType from the list of child objects.
		 *
		 * \param child EntityType object.
		 */
		void removeChild( const EntityType* );

		/*!
		 * \brief returns a state object with the given id.
		 *
		 * this function is templated. it casts the found state object
		 * to the given template argument. if the state with the given
		 * id isn't found in the list of states of the EntityType, all
		 * parent objects are queried.
		 *
		 * \param id id of the State to be returned.
		 * \return State object, if found, casted to the type of the template
		 * argument, 0 otherwise.
		 */
		template<class T>
		T state( const string &id ) const
		{
			T state = StateManager::state<T>( id );

			if ( !state && m_parent )
				state = m_parent->state<T>( id );

			return state;
		}

		/*!
		 * \brief what does this function do?!
		 *
		 * safe to remove this function.
		 */
		// TODO: remove this function.
		State* entityState( const string& );

	private:
		EntityType*		m_parent;
		EntityTypeList	m_children;
	};
} /* Baukasten */

#endif /* end of include guard: ENTITY_TYPE_XJ90PEI */
