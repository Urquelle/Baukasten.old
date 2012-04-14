#ifndef VECTOR_H_5BZOYFBV
#define VECTOR_H_5BZOYFBV

#include "math/Global"

namespace Baukasten {

	class BAUKASTEN_EXPORT Vector2 {
	public:
		Vector2();
		Vector2( const Vector2& );
		Vector2( const f32 );
		Vector2( const f32, const f32 );
		virtual ~Vector2();

		Vector2& operator=( const Vector2& );
		Vector2& operator=( const f32 );
		bool     operator==( const Vector2& ) const;
		bool     operator!=( const Vector2& ) const;
		Vector2  operator+( const Vector2& ) const;
		Vector2  operator+( const f32 ) const;
		Vector2  operator*( const Vector2& ) const;
		Vector2  operator*( const f32 ) const;
		Vector2  operator/( const Vector2& ) const;
		Vector2  operator/( const f32 ) const;
		f32      operator[]( const u32 ) const;

		f32 mag() const;
		f32 magSqr() const;
		Vector2 normalised() const;
		Vector2& normalise();
		f32 dot( const Vector2& ) const;

	private:
		f32          m_data[2];
		mutable bool m_dirty;
		mutable f32  m_mag;
	};
} /* Baukasten */

#endif /* end of include guard: VECTOR_H_5BZOYFBV */

