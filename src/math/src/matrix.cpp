#include "math/include/matrix.h"

#include "core/Assert"
#include "math/Quaternion"
#include "math/Vector3"

#include <cmath>

namespace Baukasten {

#define MATRIX_IDENT {\
		1.0f, 0.0f, 0.0f, 0.0f,\
		0.0f, 1.0f, 0.0f, 0.0f,\
		0.0f, 0.0f, 1.0f, 0.0f,\
		0.0f, 0.0f, 0.0f, 1.0f\
}

static const u8 MATRIX_SIZE = 16;
static const u8 MATRIX_BYTE_SIZE = MATRIX_SIZE * sizeof( f32 );

void
Matrix::add( const Matrix &m1, const Matrix &m2, Matrix *result )
{
	BK_ASSERT( result, "target object must not be null." );

	(*result)[M11] = m1[M11] + m2[M11];
	(*result)[M12] = m1[M12] + m2[M12];
	(*result)[M13] = m1[M13] + m2[M13];
	(*result)[M14] = m1[M14] + m2[M14];
	(*result)[M21] = m1[M21] + m2[M21];
	(*result)[M22] = m1[M22] + m2[M22];
	(*result)[M23] = m1[M23] + m2[M23];
	(*result)[M24] = m1[M24] + m2[M24];
	(*result)[M31] = m1[M31] + m2[M31];
	(*result)[M32] = m1[M32] + m2[M32];
	(*result)[M33] = m1[M33] + m2[M33];
	(*result)[M34] = m1[M34] + m2[M34];
	(*result)[M41] = m1[M41] + m2[M41];
	(*result)[M42] = m1[M42] + m2[M42];
	(*result)[M43] = m1[M43] + m2[M43];
	(*result)[M44] = m1[M44] + m2[M44];
}

void
Matrix::add( const f32 scalar, const Matrix &m1, Matrix *result )
{
	BK_ASSERT( result, "target object must not be null." );

	(*result)[M11] = m1[M11] + scalar;
	(*result)[M12] = m1[M12] + scalar;
	(*result)[M13] = m1[M13] + scalar;
	(*result)[M14] = m1[M14] + scalar;
	(*result)[M21] = m1[M21] + scalar;
	(*result)[M22] = m1[M22] + scalar;
	(*result)[M23] = m1[M23] + scalar;
	(*result)[M24] = m1[M24] + scalar;
	(*result)[M31] = m1[M31] + scalar;
	(*result)[M32] = m1[M32] + scalar;
	(*result)[M33] = m1[M33] + scalar;
	(*result)[M34] = m1[M34] + scalar;
	(*result)[M41] = m1[M41] + scalar;
	(*result)[M42] = m1[M42] + scalar;
	(*result)[M43] = m1[M43] + scalar;
	(*result)[M44] = m1[M44] + scalar;
}

void
Matrix::decompose( const Matrix &m, Vector3 *scale, Vector3 *translation,
		Quaternion *rotation )
{
	// compute scale
	if ( scale ) {
		*scale = { m.row(1).mag(), m.row(2).mag(), m.row(3).mag() };
	}

	// compute translation
    if ( translation ) {
		*translation = m.row(4);
    }

    if ( rotation == NULL )
        return;

	// get the normalised vectors
	auto xAxis = m.row(1).normalise();
	auto yAxis = m.row(2).normalise();
	auto zAxis = m.row(3).normalise();

	// source http://www.flipcode.com/documents/matrfaq.html#Q55
	/*
		The process is performed in the following stages, which are as follows:

		Calculate the trace of the matrix T from the equation:

                  2     2     2
		T = 4 - 4x  - 4y  - 4z
                     2    2    2
			= 4( 1 -x  - y  - z )
			= mat[0] + mat[5] + mat[10] + 1
	*/
	f32 trace = xAxis.x + yAxis.y + zAxis.z + 1.0f;

	/*
		If the trace of the matrix is greater than zero, then
		perform an "instant" calculation.

		S = 0.5 / sqrt(T)
		W = 0.25 / S
		X = ( mat[9] - mat[6] ) * S
		Y = ( mat[2] - mat[8] ) * S
		Z = ( mat[4] - mat[1] ) * S
	*/
	if ( trace > BK_MATH_EPSILON ) {
		f32 s = 0.5f / sqrt( trace );
		rotation->x = ( zAxis.y - yAxis.z ) * s;
		rotation->y = ( xAxis.z - zAxis.x ) * s;
		rotation->z = ( yAxis.x - xAxis.y ) * s;
		rotation->w = 0.25f / s;
	} else {

		/*
			If the trace of the matrix is less than or equal to zero
			then identify which major diagonal element has the greatest
			value.

			Depending on this value, calculate the following:

			Column 0:
				S  = sqrt( 1.0 + mr[0] - mr[5] - mr[10] ) * 2;
				Qx = 0.5 / S;
				Qy = (mr[1] + mr[4] ) / S;
				Qz = (mr[2] + mr[8] ) / S;
				Qw = (mr[6] + mr[9] ) / S;
		*/
		if ( xAxis.x > yAxis.y && xAxis.x > zAxis.z ) {
			f32 s = sqrt( 1.0f + xAxis.x - yAxis.y - zAxis.z ) * 2.0f;
			rotation->x = 0.5f * s;
			rotation->y = ( xAxis.y + yAxis.x ) / s;
			rotation->z = ( xAxis.z + zAxis.x ) / s;
			rotation->w = ( zAxis.y + yAxis.z ) / s;
		/*
			Column 1:
				S  = sqrt( 1.0 + mr[5] - mr[0] - mr[10] ) * 2;
				Qx = (mr[1] + mr[4] ) / S;
				Qy = 0.5 / S;
				Qz = (mr[6] + mr[9] ) / S;
				Qw = (mr[2] + mr[8] ) / S;
		*/
		} else if ( yAxis.y > zAxis.z ) {
			f32 s = sqrt( 1.0f + yAxis.y - xAxis.x - zAxis.z ) * 2.0f;
			rotation->x = ( xAxis.y + yAxis.x ) / s;
			rotation->y = 0.5f * s;
			rotation->z = ( yAxis.z + zAxis.y ) / s;
			rotation->w = ( xAxis.z + zAxis.x ) / s;
		/*
			Column 2:
				S  = sqrt( 1.0 + mr[10] - mr[0] - mr[5] ) * 2;
				Qx = (mr[2] + mr[8] ) / S;
				Qy = (mr[6] + mr[9] ) / S;
				Qz = 0.5 / S;
				Qw = (mr[1] + mr[4] ) / S;
		*/
		} else {
			f32 s = sqrt( 1.0f + zAxis.z - xAxis.x - yAxis.y ) * 2.0f;
			rotation->w = ( xAxis.y + yAxis.x ) / s;
			rotation->x = ( xAxis.z + zAxis.x ) / s;
			rotation->y = ( yAxis.z + zAxis.y ) / s;
			rotation->z = 0.5f * s;
		}
	}
}

Matrix&
Matrix::identity()
{
	static Matrix m( MATRIX_IDENT );
	return m;
}

bool
Matrix::isRegular( const Matrix &m )
{
	return ( m.det() != 0 );
}

void
Matrix::multiply( const Matrix &m1, const Matrix &m2, Matrix *result )
{
	BK_ASSERT( result, "target object must not be null." );

    f32 t[16];

    t[0]  = m1[M11] * m2[M11] + m1[M21] * m2[M12] + m1[M31] * m2[M13] + m1[M41] * m2[M14];
    t[1]  = m1[M12] * m2[M11] + m1[M22] * m2[M12] + m1[M32] * m2[M13] + m1[M42] * m2[M14];
    t[2]  = m1[M13] * m2[M11] + m1[M23] * m2[M12] + m1[M33] * m2[M13] + m1[M43] * m2[M14];
    t[3]  = m1[M14] * m2[M11] + m1[M24] * m2[M12] + m1[M34] * m2[M13] + m1[M44] * m2[M14];

    t[4]  = m1[M11] * m2[M21] + m1[M21] * m2[M22] + m1[M31] * m2[M23] + m1[M41] * m2[M24];
    t[5]  = m1[M12] * m2[M21] + m1[M22] * m2[M22] + m1[M32] * m2[M23] + m1[M42] * m2[M24];
    t[6]  = m1[M13] * m2[M21] + m1[M23] * m2[M22] + m1[M33] * m2[M23] + m1[M43] * m2[M24];
    t[7]  = m1[M14] * m2[M21] + m1[M24] * m2[M22] + m1[M34] * m2[M23] + m1[M44] * m2[M24];

    t[8]  = m1[M11] * m2[M31] + m1[M21] * m2[M32] + m1[M31] * m2[M33] + m1[M41] * m2[M34];
    t[9]  = m1[M12] * m2[M31] + m1[M22] * m2[M32] + m1[M32] * m2[M33] + m1[M42] * m2[M34];
    t[10] = m1[M13] * m2[M31] + m1[M23] * m2[M32] + m1[M33] * m2[M33] + m1[M43] * m2[M34];
    t[11] = m1[M14] * m2[M31] + m1[M24] * m2[M32] + m1[M34] * m2[M33] + m1[M44] * m2[M34];

    t[12] = m1[M11] * m2[M41] + m1[M21] * m2[M42] + m1[M31] * m2[M43] + m1[M41] * m2[M44];
    t[13] = m1[M12] * m2[M41] + m1[M22] * m2[M42] + m1[M32] * m2[M43] + m1[M42] * m2[M44];
    t[14] = m1[M13] * m2[M41] + m1[M23] * m2[M42] + m1[M33] * m2[M43] + m1[M43] * m2[M44];
    t[15] = m1[M14] * m2[M41] + m1[M24] * m2[M42] + m1[M34] * m2[M43] + m1[M44] * m2[M44];

	*result = t;
}

Vector3
Matrix::scale( const Matrix &m )
{
	Vector3 s;
	Matrix::decompose( m, &s, NULL, NULL );
	return s;
}

void
Matrix::subtract( const Matrix &m1, const Matrix &m2, Matrix *result )
{
	BK_ASSERT( result, "target object must not be null." );

	(*result)[M11] = m1[M11] - m2[M11];
	(*result)[M12] = m1[M12] - m2[M12];
	(*result)[M13] = m1[M13] - m2[M13];
	(*result)[M14] = m1[M14] - m2[M14];
	(*result)[M21] = m1[M21] - m2[M21];
	(*result)[M22] = m1[M22] - m2[M22];
	(*result)[M23] = m1[M23] - m2[M23];
	(*result)[M24] = m1[M24] - m2[M24];
	(*result)[M31] = m1[M31] - m2[M31];
	(*result)[M32] = m1[M32] - m2[M32];
	(*result)[M33] = m1[M33] - m2[M33];
	(*result)[M34] = m1[M34] - m2[M34];
	(*result)[M41] = m1[M41] - m2[M41];
	(*result)[M42] = m1[M42] - m2[M42];
	(*result)[M43] = m1[M43] - m2[M43];
	(*result)[M44] = m1[M44] - m2[M44];
}

void
Matrix::subtract( const f32 scalar, const Matrix &m1, Matrix *result )
{
	BK_ASSERT( result, "target object must not be null." );

	(*result)[M11] = m1[M11] - scalar;
	(*result)[M12] = m1[M12] - scalar;
	(*result)[M13] = m1[M13] - scalar;
	(*result)[M14] = m1[M14] - scalar;
	(*result)[M21] = m1[M21] - scalar;
	(*result)[M22] = m1[M22] - scalar;
	(*result)[M23] = m1[M23] - scalar;
	(*result)[M24] = m1[M24] - scalar;
	(*result)[M31] = m1[M31] - scalar;
	(*result)[M32] = m1[M32] - scalar;
	(*result)[M33] = m1[M33] - scalar;
	(*result)[M34] = m1[M34] - scalar;
	(*result)[M41] = m1[M41] - scalar;
	(*result)[M42] = m1[M42] - scalar;
	(*result)[M43] = m1[M43] - scalar;
	(*result)[M44] = m1[M44] - scalar;
}

Vector3
Matrix::translation( const Matrix &m )
{
	Vector3 t;
	Matrix::decompose( m, NULL, &t, NULL );
	return t;
}

void
Matrix::transpose( const Matrix &m, Matrix *result )
{
	f32 t[MATRIX_SIZE];

	t[M11] = m.get( M11 ); t[M12] = m.get( M21 ); t[M13] = m.get( M31 ); t[M14] = m.get( M41 );
	t[M21] = m.get( M12 ); t[M22] = m.get( M22 ); t[M23] = m.get( M32 ); t[M24] = m.get( M42 );
	t[M31] = m.get( M13 ); t[M22] = m.get( M23 ); t[M23] = m.get( M33 ); t[M24] = m.get( M43 );
	t[M41] = m.get( M14 ); t[M22] = m.get( M24 ); t[M23] = m.get( M34 ); t[M24] = m.get( M44 );

	*result = t;
}

Matrix&
Matrix::zero()
{
	static Matrix m({
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	});

	return m;
}

Matrix::Matrix() :
	Vector( MATRIX_IDENT )
{
}

Matrix::Matrix( initializer_list<f32> list ) :
	Vector( list )
{
}

Matrix::Matrix( const f32 *values ) :
	Vector({
		values[0],  values[1],  values[2],  values[3],
		values[4],  values[5],  values[6],  values[7],
		values[8],  values[9],  values[10], values[11],
		values[12], values[13], values[14], values[15]
	})
{
}

Matrix::Matrix( const Matrix &other ) :
	Vector({
		other[0],  other[1],  other[2],  other[3],
		other[4],  other[5],  other[6],  other[7],
		other[8],  other[9],  other[10], other[11],
		other[12], other[13], other[14], other[15]
	})
{
}

Matrix::~Matrix()
{
}

void
Matrix::add( const f32 scalar )
{
	Vector::add( scalar );
}

void
Matrix::add( const Matrix &other )
{
	Vector::add( other );
}

Vector3
Matrix::row( const u32 r ) const
{
	BK_ASSERT( r > 0 && r <= 4, "row has to be in the range [1,4].");

	u32 offset = ( r - 1 ) * 4;
	return Vector3( get( offset ), get( offset + 1 ), get( offset + 2 ) );
}

f32
Matrix::det() const
{
	f32 a11 = get(M11)*(
		get(M22)*get(M33)*get(M44)+get(M23)*get(M34)*get(M42)+get(M24)*get(M32)*get(M43)-
		get(M24)*get(M33)*get(M42)-get(M22)*get(M34)*get(M43)-get(M23)*get(M32)*get(M44)
	);

	f32 a12 = get(M12)*(
		get(M21)*get(M33)*get(M44)+get(M23)*get(M34)*get(M41)+get(M24)*get(M31)*get(M43)-
		get(M24)*get(M33)*get(M41)-get(M21)*get(M34)*get(M43)-get(M23)*get(M31)*get(M44)
	);

	f32 a13 = get(M13)*(
		get(M21)*get(M32)*get(M44)+get(M22)*get(M34)*get(M41)+get(M24)*get(M31)*get(M42)-
		get(M24)*get(M32)*get(M41)-get(M21)*get(M34)*get(M42)+get(M22)*get(M31)*get(M44)
	);

	f32 a14 = get(M14)*(
		get(M21)*get(M32)*get(M43)+get(M22)*get(M33)*get(M41)+get(M23)*get(M31)*get(M42)-
		get(M23)*get(M32)*get(M41)-get(M21)*get(M33)*get(M42)-get(M22)*get(M31)*get(M43)
	);

	return a11-a12+a13-a14;
}

void
Matrix::decompose( Vector3 *scale, Vector3 *translation,
		Quaternion *rotation )
{
	Matrix::decompose( *this, scale, translation, rotation );
}

bool
Matrix::isRegular() const
{
	return Matrix::isRegular( *this );
}

void
Matrix::multiply( const f32 scalar )
{
	Vector::multiply( scalar );
}

void
Matrix::multiply( const Matrix &other )
{
	Matrix::multiply( *this, other, this );
}

void
Matrix::subtract( const f32 scalar )
{
	Matrix::subtract( scalar, *this, this );
}

void
Matrix::subtract( const Matrix &m )
{
	Matrix::subtract( *this, m, this );
}

void
Matrix::transpose()
{
	Matrix::transpose( *this, this );
}

Matrix
Matrix::operator+( const Matrix &other ) const
{
	Matrix result( *this );
	result.add( other );
	return result;
}

Matrix
Matrix::operator+( const f32 scalar ) const
{
	Matrix result( *this );
	result.add( scalar );
	return result;
}

Matrix&
Matrix::operator+=( const Matrix &other )
{
	add( other );
	return *this;
}

Matrix&
Matrix::operator+=( const f32 scalar )
{
	add( scalar );
	return *this;
}

Matrix
Matrix::operator*( const Matrix &other ) const
{
	Matrix result( *this );
	result.multiply( other );
	return result;
}

Matrix
Matrix::operator*( const f32 scalar ) const
{
	Matrix result( *this );
	result.multiply( scalar );
	return result;
}

Matrix&
Matrix::operator*=( const Matrix &other )
{
	multiply( other );
	return *this;
}

Matrix&
Matrix::operator*=( const f32 scalar )
{
	multiply( scalar );
	return *this;
}

bool
Matrix::operator==( const Matrix &other )
{
	return (
		( get(M11) - other.get(M11) ) < BK_MATH_EPSILON &&
		( get(M12) - other.get(M12) ) < BK_MATH_EPSILON &&
		( get(M13) - other.get(M13) ) < BK_MATH_EPSILON &&
		( get(M14) - other.get(M14) ) < BK_MATH_EPSILON &&
		( get(M21) - other.get(M21) ) < BK_MATH_EPSILON &&
		( get(M22) - other.get(M22) ) < BK_MATH_EPSILON &&
		( get(M23) - other.get(M23) ) < BK_MATH_EPSILON &&
		( get(M24) - other.get(M24) ) < BK_MATH_EPSILON &&
		( get(M31) - other.get(M31) ) < BK_MATH_EPSILON &&
		( get(M32) - other.get(M32) ) < BK_MATH_EPSILON &&
		( get(M33) - other.get(M33) ) < BK_MATH_EPSILON &&
		( get(M34) - other.get(M34) ) < BK_MATH_EPSILON &&
		( get(M41) - other.get(M41) ) < BK_MATH_EPSILON &&
		( get(M42) - other.get(M42) ) < BK_MATH_EPSILON &&
		( get(M43) - other.get(M43) ) < BK_MATH_EPSILON &&
		( get(M44) - other.get(M44) ) < BK_MATH_EPSILON
	);
}

bool
Matrix::operator!=( const Matrix &other )
{
	return !operator==( other );
}

} /* Baukasten */
