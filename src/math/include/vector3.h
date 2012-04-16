#ifndef VECTOR3_H_JDMENO72
#define VECTOR3_H_JDMENO72

#include "math/Global"

namespace Baukasten {

	class BAUKASTEN_EXPORT Vector3 {
	public:
		Vector3();
		Vector3( const Vector3& );
		Vector3( const f32 );
		Vector3( const f32, const f32, const f32 );
		virtual ~Vector3();

		Vector3& operator=( const Vector3& );
		Vector3& operator=( const f32 );
		bool     operator==( const Vector3& ) const;
		bool     operator!=( const Vector3& ) const;
		Vector3  operator+( const Vector3& ) const;
		Vector3  operator+( const f32 ) const;
		Vector3  operator*( const Vector3& ) const;
		Vector3  operator*( const f32 ) const;
		Vector3  operator/( const Vector3& ) const;
		Vector3  operator/( const f32 ) const;
		f32      operator[]( const u32 ) const;

		void     set( const u32, const f32 );

		f32      mag() const;
		f32      magSqr() const;
		Vector3  normalised() const;
		Vector3& normalise();
		f32      dot( const Vector3& ) const;
		Vector3  cross( const Vector3& ) const;

	private:
		f32          m_data[3];
		mutable bool m_dirty;
		mutable f32  m_mag;
	};
} /* Baukasten */


#endif /* end of include guard: VECTOR3_H_JDMENO72 */

