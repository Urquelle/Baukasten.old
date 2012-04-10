#ifndef MODEL_INTERFACE_H_LUKQTDNO
#define MODEL_INTERFACE_H_LUKQTDNO

#include "model/Global"

namespace Baukasten {

	class GameEntity;
	class ModelInterfacePrivate;

	// hier können alle speicher allozierungen kontrolliert werden.
	// zusätzlich kann hier der baum von objekten vorgehalten werden, und
	// für jedes objekt eine eindeutige id erstellt werden.
	// damit das funktioniert, müssen natürlich alle konstruktoren der objekte
	// privat gemacht werden, und die ModelInterface klasse als ihr friend
	// deklariert werden.
	/*!
	 * \ingroup model
	 * @{
	 *
	 * \addtogroup interface
	 * @{
	 *
	 * \class ModelInterface
	 * \headerfile ModelInterface "model/ModelInterface"
	 * \brief model interface class.
	 *
	 * provides access to methods that manage GameEntity objects. this class is
	 * implemented as a singleton and is meant to be the only interface to
	 * use to create and destroy GameEntity objects in order to provide easier
	 * control of memory and ownership.
	 */
	class BAUKASTEN_EXPORT ModelInterface {
	public:

		/*! destructor. */
		virtual ~ModelInterface();

		/*!
		 * \brief create an instance of a GameEntity.
		 *
		 * creates a new instance of a GameEntity with the given id. the given id
		 * can be chosen arbitrarily as no validation of uniqueness takes place
		 * at this stage. on insertion an internal and *unique* id is created and
		 * assigned.
		 *
		 * \note if parent is NULL, the created entity becomes the root element.
		 * if root element is already present the application exits.
		 */
		GameEntity* createEntity( const string&, GameEntity *parent = 0 );

		/*!
		 * \brief destroys a GameEntity object.
		 *
		 * if an object with the given unique id is found in the collection, it
		 * is removed from the entity collection and its destructor is called.
		 *
		 * \note all child entities that are assigned to the object that is destroyed
		 * are deleted as well!
		 *
		 * \param id unique id of the object.
		 */
		void destroyEntity( const u32 );

		/*!
		 * \brief destroys a GameEntity object.
		 *
		 * if the given object is found in the collection, it
		 * is removed from the entity collection and its destructor is called.
		 *
		 * \note all child entities that are assigned to the object that is destroyed
		 * are deleted as well!
		 *
		 * \param entity GameEntity object.
		 */
		void destroyEntity( GameEntity* );

		/*!
		 * \brief retrieve a GameEntity object.
		 *
		 * searches for and returns a GameEntity object with the given
		 * unique id in the collection.
		 *
		 * \param id unique id of the object.
		 * \return GameEntity object if found, 0 otherwise.
		 */
		GameEntity* entity( const u32 );

		/*!
		 * \brief returns number of elements in the collection.
		 * \return u32 value representing the number of elements.
		 */
		u32 entityCount() const;

		/*!
		 * \brief singleton method to retrieve interface object.
		 *
		 * singleton method which provides the interface to retrieve
		 * the object implementing the methods.
		 *
		 * \return pointer to an ModelInterface object.
		 */
		static ModelInterface& instance();

		/*!
		 * \brief cleans up the collection.
		 *
		 * the entity list is cleared and all objects are destroyed.
		 */
		void shutdown();

		/*!
		 * \brief retrieve the unique id of the object.
		 * \return u32 value of the unique id.
		 * \param entity GameEntity object to which the id is returned.
		 */
		u32 uniqueId( const GameEntity* ) const;

	private:
		ModelInterface();
		ModelInterface( const ModelInterface& );
		ModelInterface& operator=( const ModelInterface& );

		static ModelInterface* m_instance;
		BK_PIMPL_PTR( ModelInterface );
	};
	/** @} */
	/** @} */
} /* Baukasten  */

#endif /* end of include guard: MODEL_INTERFACE_H_LUKQTDNO */

