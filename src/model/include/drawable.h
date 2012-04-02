#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "model/Global"

#include "core/Core"
#include "model/Entity"

namespace Baukasten {

	/*!
	 * \brief represents a drawable object.
	 *
	 * \ingroup model entity
	 *
	 * \headerfile Drawable "model/Drawable"
	 *
	 * drawable objects can be stored in the VirtualSpace
	 * map and be rendered by whatever rendering engine is used.
	 */
	class BAUKASTEN_EXPORT Drawable : public Entity {
	public:

		/*!
		 * \brief constructor
		 *
		 * \param id object id.
		 */
		Drawable( const string& );

		/*! \brief destructor */
		virtual ~Drawable();

		/*!
		 * \brief renders the object
		 *
		 * render method is called once every iteration of
		 * the mainloop.
		 */
		virtual void render() = 0;

		/*!
		 * \brief set position of the object.
		 *
		 * \param position a three point vector which represents
		 * the position of the object in a 3d space.
		 */
		void setPosition( const vec3f );

		/*! \brief getter method for position. */
		const vec3f position() const;

		void setSize( const vec2f );

		const vec2f size() const;

		/*!
		 * \brief set the rotation around the x-axis.
		 *
		 * \param pitch rotation value.
		 */
		void setPitch( const f32 );

		/*! getter method for the rotation around the x-axis. */
		const f32 pitch() const;

		/*! setter method for object's rotation around the y-axis. */
		void setYaw( const f32 );

		/*! getter method for object's rotation around the y-axis. */
		const f32 yaw() const;

		/*! setter method for object's rotation around the z-axis. */
		void setRoll( const f32 );

		/*! getter method for object's rotation around the z-axis. */
		const f32 roll() const;

		/*! setter method for object's scale ratio. */
		void setScale( const f32 );

		/*! getter method for object's scale ratio. */
		const f32 scale() const;

	protected:
		// position of the object
		vec3f m_position;

		// size of the object
		vec2f m_size;

		// orientation the object is looking at
		vec3f m_orientation;

		// rotation about the x-axis
		f32 m_pitch;

		// rotation about the y-axis
		f32 m_yaw;

		// rotation about the z-axis
		f32 m_roll;

		// scaling factor of the object
		f32 m_scale;
	};
}

#endif // RENDERABLE_ENTITY_H
