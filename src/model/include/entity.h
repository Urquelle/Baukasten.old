#ifndef ENTITY_H
#define ENTITY_H

#include "model/Global"

#include <string>

/*! \brief Mainnamespace of the Project.
 *
 * All Classes of the Project are inside this namespace.
 */
namespace Baukasten {
	/*! \defgroup entity Entity Classes */

	/*! \brief baseclass.
	 *
	 * \ingroup entity
	 *
	 * baseclass with an id field.
	 */
	class BAUKASTEN_EXPORT Entity {
	public:
		/*! constructor
		 *
		 * \param id a string which becomes the id of the object.
		 */
		Entity( const string& );

		/*! Destructor */
		virtual ~Entity();

		/*! \brief implementation of the assignment operator.
		 *
		 * the id field of the rhs object is assigned to the lhs object.
		 *
		 * \param other an entity object to take the id from.
		 * \return a reference to the lhs object.
		 */
		Entity& operator=( const Entity& );

		/*! \brief implementation of the compare operator.
		 *
		 * compares the fields of both objects.
		 *
		 * \param other an object to compare with.
		 * \return bool true if both objects have the same id.
		 */
		bool operator==( const Entity& ) const;

		/*! \brief getter method for the id member variable.
		 *
		 * \return the id of the object.
		 */
		string id() const;

	private:
		string m_id;
	};
}

#endif // ENTITY_H

