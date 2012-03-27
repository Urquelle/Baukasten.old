#ifndef ENTITY_H
#define ENTITY_H

#include "model/Global"

namespace Baukasten {
	/*!
	 * \brief base class in the model module.
	 *
	 * \ingroup model entity
	 *
	 * \headerfile Entity "model/Entity"
	 *
	 * base class with an id field.
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
		 * \param other an Entity object to be copied from.
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

