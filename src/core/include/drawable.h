#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "global.h"
#include "../../util/Util"

#include "entity.h"

namespace Baukasten {

	/*! \brief represents a drawable object.
	 *
	 * \ingroup entity
	 *
	 * drawable objects can be stored in the VirtualSpace
	 * map and be rendered by whatever rendering engine is used.
	 */
	class BAUKASTEN_EXPORT Drawable : public Entity {
	public:

		/*! \brief constructor
		 *
		 * \param id object id.
		 */
		Drawable( const std::string& );

		/*! \brief destructor */
		virtual ~Drawable();

		/*! \brief renders the object
		 *
		 * render method is called once every iteration of
		 * the mainloop.
		 */
		virtual void render() = 0;

		/*! \brief set position of the object.
		 *
		 * \param position a three point vector which represents
		 * the position of the object in a 3d space.
		 */
		void setPosition( const vec3<float> );

		/*! \brief getter method for position. */
		const vec3<float> position() const;

		void setSize( const vec2<float> );

		const vec2<float> size() const;

		/*! \brief set the rotation around the x-axis.
		 *
		 * \param pitch rotation value.
		 */
		void setPitch( const float );

		/*! getter method for the rotation around the x-axis. */
		const float pitch() const;

		/*! setter method for object's rotation around the y-axis. */
		void setYaw( const float );

		/*! getter method for object's rotation around the y-axis. */
		const float yaw() const;

		/*! setter method for object's rotation around the z-axis. */
		void setRoll( const float );

		/*! getter method for object's rotation around the z-axis. */
		const float roll() const;

		/*! setter method for object's scale ratio. */
		void setScale( const float );

		/*! getter method for object's scale ratio. */
		const float scale() const;

		/*! sets the visibility of the object. */
		virtual void setVisible( bool );

	protected:
		// position of the object
		vec3<float>   mPosition;

		// size of the object
		vec2<float>	mSize;

		// orientation the object is looking at
		vec3<float>	mOrientation;

		// rotation around the x-axis
		float   mPitch;

		// rotation around the y-axis
		float   mYaw;

		// rotation around the z-axis
		float   mRoll;

		// scaling factor of the object
		float   mScale;
	};
}

#endif // RENDERABLE_ENTITY_H
