#ifndef VECTOR_H_5BZOYFBV
#define VECTOR_H_5BZOYFBV

#include "math/Global"
#include "math/Vector"

namespace Baukasten {

	class BAUKASTEN_EXPORT Vector2 : public Vector<f32, 2> {
		typedef Vector<f32, 2> Type;
	public:
		Vector2();
		Vector2( const Vector2& );
		Vector2( const f32 );
		Vector2( const f32, const f32 );
		virtual ~Vector2();

		Vector2&           operator=( const Vector2& );
		Vector2&           operator=( const f32 );
		bool               operator==( const Vector2& ) const;
		bool               operator!=( const Vector2& ) const;
		Vector2            operator+( const Vector2& ) const;
		Vector2            operator+( const f32 ) const;
		Vector2            operator*( const Vector2& ) const;
		Vector2            operator*( const f32 ) const;
		Vector2            operator/( const Vector2& ) const;
		Vector2            operator/( const f32 ) const;

		f32                mag() const;
		f32                magSqr() const;
		Vector2            normalised() const;
		Vector2&           normalise();
		f32                dot( const Vector2& ) const;

		f32 &x;
		f32 &y;
	};
} /* Baukasten */

#endif /* end of include guard: VECTOR_H_5BZOYFBV */

