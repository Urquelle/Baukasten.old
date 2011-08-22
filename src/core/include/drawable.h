#ifndef RENDERABLE_ENTITY_H
#define RENDERABLE_ENTITY_H

#include "global.h"
#include "entity.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT Drawable : public Entity {
	public:
		Drawable( const std::string& );
		virtual ~Drawable();

		void setPosition( const t_pos );
		const t_pos getPosition() const;

		void setPitch( const float );
		const float getPitch() const;

		void setYaw( const float );
		const float getYaw() const;

		void setRoll( const float );
		const float getRoll() const;

		void setScale( const float );
		const float getScale() const;

	protected:
		// position of the object
		t_pos   mPosition;

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
