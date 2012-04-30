#ifndef QUATERNION_H_VYWK3DFI
#define QUATERNION_H_VYWK3DFI

#include "math/Global"
#include "math/Vector"

namespace Baukasten {
	class Matrix;
	class Vector3;

	/*!
	 * \brief Quaternion class declaration.
	 */
	class BAUKASTEN_EXPORT Quaternion : public Vector<f32, 4> {
		typedef Vector<f32, 4> Type;
		typedef Type::VectorProxy VectorProxy;
	public:
		Quaternion();
		Quaternion( const f32, const f32, const f32, const f32 );
		Quaternion( const f32* );
		Quaternion( const Quaternion& );
		Quaternion( const Matrix& );
		Quaternion( const Vector3&, const f32 );
		virtual ~Quaternion();

		Quaternion&        operator=( const Quaternion& );
		const VectorProxy  operator[]( const u32 ) const;
		VectorProxy        operator[]( const u32 );

		f32 &x;
		f32 &y;
		f32 &z;
		f32 &w;
	private:
	};
} /* Baukasten */

#endif /* end of include guard: QUATERNION_H_VYWK3DFI */

