#ifndef MATRIX_H_EQYZZ7PG
#define MATRIX_H_EQYZZ7PG

#include "math/Global"
#include "math/Vector"

namespace Baukasten {

	class Vector3;
	class Quaternion;

	/*!
	 * \brief Matrix class declaration.
	 */
	class BAUKASTEN_EXPORT Matrix : public Vector<f32, 16> {
	public:
		enum MatrixField {
			M11 =  0, M12 =  1, M13 =  2, M14 =  3,
			M21 =  4, M22 =  5, M23 =  6, M24 =  7,
			M31 =  8, M32 =  9, M33 = 10, M34 = 11,
			M41 = 12, M42 = 13, M43 = 14, M44 = 15
		};

		Matrix();
		Matrix( initializer_list<f32> );
		Matrix( const f32* );
		Matrix( const Matrix& );
		virtual ~Matrix();

		static void        add( const Matrix&, const Matrix&, Matrix* );
		static void        add( const f32, const Matrix&, Matrix* );
		static void        decompose( const Matrix&, Vector3*,
										Vector3*, Quaternion* );
		static Matrix&     identity();
		static bool        isRegular( const Matrix& );
		static void        multiply( const Matrix&, const Matrix&, Matrix* );
		static void        multiply( const f32, const Matrix&, Matrix* );
		static Quaternion  rotation( const Matrix& );
		static Vector3     scale( const Matrix& );
		static void        subtract( const Matrix&, const Matrix&, Matrix* );
		static void        subtract( const f32, const Matrix&, Matrix* );
		static Vector3     translation( const Matrix& );
		static void        transpose( const Matrix&, Matrix* );
		static Matrix&     zero();

		void               add( const f32 );
		void               add( const Matrix& );
		f32                det() const;
		void               decompose( Vector3*, Vector3*, Quaternion* );
		bool               isRegular() const;
		void               multiply( const f32 );
		void               multiply( const Matrix& );
		Vector3            row( const u32 ) const;
		void               subtract( const f32 );
		void               subtract( const Matrix& );
		void               transpose();

		Matrix             operator+( const Matrix& ) const;
		Matrix             operator+( const f32 ) const;
		Matrix&            operator+=( const Matrix& );
		Matrix&            operator+=( const f32 );
		Matrix             operator*( const Matrix& ) const;
		Matrix             operator*( const f32 ) const;
		Matrix&            operator*=( const Matrix& );
		Matrix&            operator*=( const f32 );
		bool               operator==( const Matrix& );
		bool               operator!=( const Matrix& );
	};
} /* Baukasten */

#endif /* end of include guard: MATRIX_H_EQYZZ7PG */

