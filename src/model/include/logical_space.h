#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "model/Global"

namespace Baukasten {

	/*!
	 * \ingroup model
	 * @{
	 *
	 * \addtogroup space
	 * @{
	 *
	 * \class LogicalSpace
	 * \headerfile LogicalSpace "model/LogicalSpace"
	 * \brief logical space class.
	 *
	 * implementation of the logical space entity in the model. the
	 * logical space contains all GameEntities those actions get
	 * executed in the main game loop.
	 */
	class BAUKASTEN_EXPORT LogicalSpace {
	public:

		/*! constructor. */
		LogicalSpace();

		/*! destructor. */
		virtual ~LogicalSpace();

		/*!
		 * \brief run actions.
		 *
		 * runs actions of every GameEntity in the collection.
		 */
		void runActions();

		/*!
		 * \brief get a GameEntity from the collection.
		 *
		 * returns a GameEntity object that is stored under the
		 * given id in the collection.
		 *
		 * \return pointer to the GameEntity if found, 0 otherwise.
		 */
		GameEntity* entity( const string& ) const;

		/*!
		 * \brief add an entity to the collection.
		 *
		 * adds a GameEntity object to the collection and stores it
		 * under the given id.
		 *
		 * \note in debug mode the application exits with a debug message if
		 * the provided id is already in the collection.
		 */
		void addEntity( const string&, GameEntity* );

		/*!
		 * \brief add an entity to the collection.
		 *
		 * convenience method, where the object's id is taken
		 * as the key for the collection.
		 *
		 * \sa addEntity( const string&, GameEntity* )
		 */
		void addEntity( GameEntity* );

		/*!
		 * \brief get the entity collection.
		 * \return list containing all entities in the collection.
		 * \todo use vector.
		 */
		list<GameEntity*> entities() const;

		/*!
		 * \brief query collection for entities presence.
		 * \return true if given id is present in the collection, false otherwise.
		 */
		bool hasEntity( const string& ) const;

		/*! remove entity from the collection. */
		void removeEntity( const string& );

	private:
		list<GameEntity*>			m_list;
		map<string, GameEntity*>	m_map;
	};
	/** @} */
	/** @} */
}

#endif // LOGICAL_SPACE_H

