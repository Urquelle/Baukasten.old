#ifndef ENTITY_MANAGER_ZCJZL2J5
#define ENTITY_MANAGER_ZCJZL2J5

#include "model/GenericManager"
#include "model/Global"

namespace Baukasten {

	/*!
	 * \ingroup model
	 * @{
	 *
	 * \addtogroup entity
	 * @{
	 *
	 * \class EntityManager
	 * \brief manager class, with Entity specialisation.
	 * \headerfile EntityManager "model/EntityManager"
	 *
	 * implements manager methods to operate upon Entity classes.
	 */
	class BAUKASTEN_EXPORT EntityManager :
		protected virtual GenericManager<Entity> {
	public:
		/*! \brief constructor */
		EntityManager();

		/*! \brief destructor */
		virtual ~EntityManager();

		/*!
		 * \brief adds an Entity to the collection.
		 *
		 * \sa addEntity( const string&, Entity* )
		 *
		 * \param entity Entity object to add to the collection.
		 */
		void addEntity( Entity* );

		/*!
		 * \brief adds an Entity to the collection.
		 *
		 * adds the given Entity object to the collection. this Entity
		 * is stored under the given id as the key.
		 *
		 * \param id id of the Entity to be stored under.
		 * \param entity Entity object to add to the collection.
		 */
		void addEntity( const string&, Entity* );

		/*!
		 * \brief retrieve an Entity object to the id.
		 *
		 * retrieve an Entity object to the given id.
		 *
		 * \return pointer to an Entity object if found, 0 otherwise.
		 */
		Entity* entity( const string& ) const;

		/*!
		 * \brief fetch the collection.
		 *
		 * retrieve the map of all stored Entities.
		 *
		 * \return map of Entity objects.
		 */
		TMap entities() const;

		/*!
		 * \brief query collection for the existance of an id.
		 *
		 * \return true if the given id is in the collection, false otherwise.
		 *
		 * \param id id that is being searched for.
		 */
		bool hasEntity( const string& ) const;

		/*!
		 * \brief remove an Entity from the collection.
		 *
		 * removes an Entity from the collection under the
		 * given id.
		 *
		 * \param id id of the Entity that is to be removed.
		 */
		void removeEntity( const string& );
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: ENTITY_MANAGER_ZCJZL2J5 */
