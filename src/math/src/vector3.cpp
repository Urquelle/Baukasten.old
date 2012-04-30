#include "math/include/vector3.h"

#include "core/Assert"

#include <cfloat>
#include <cmath>

using namespace Baukasten;
using namespace std;

Vector3::Vector3() :
	Vector(),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] )
{
}

Vector3::Vector3( const Vector3 &other ) :
	Vector({ other.x, other.y, other.z }),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] )
{
}

Vector3::Vector3( const f32 value ) :
	Vector({ value, value, value }),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] )
{
}

Vector3::Vector3( const f32 _f, const f32 _s, const f32 _t ) :
	Vector({ _f, _s, _t }),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] )
{
}

Vector3::~Vector3()
{
}

Vector3&
Vector3::operator=( const Vector3 &other )
{
	if ( this == &other )
		return *this;

	Type::operator=( other );
	return *this;
}

Vector3&
Vector3::operator=( const f32 value )
{
	Type::operator=({ value, value, value });
	return *this;
}

bool
Vector3::operator==( const Vector3 &other ) const
{
	if (
		fabs( x - other.x ) < BK_MATH_EPSILON &&
		fabs( y - other.y ) < BK_MATH_EPSILON &&
		fabs( z - other.z ) < BK_MATH_EPSILON
	) return true;

	return false;
}

bool
Vector3::operator!=( const Vector3 &other ) const
{
	return !operator==( other );
}

Vector3
Vector3::operator+( const Vector3 &other ) const
{
	return Vector3( x + other.x, y + other.y, z + other.z );
}

Vector3
Vector3::operator+( const f32 value ) const
{
	return Vector3( x + value, y + value, z + value );
}

Vector3
Vector3::operator*( const Vector3 &other ) const
{
	return Vector3( x * other.x, y * other.y, z * other.z );
}

Vector3
Vector3::operator*( const f32 value ) const
{
	return Vector3( x * value, y * value, z * value );
}

Vector3
Vector3::operator/( const Vector3 &other ) const
{
	return Vector3(
		( other.x != 0 ) ? x / other.x : FLT_MAX,
		( other.y != 0 ) ? y / other.y : FLT_MAX,
		( other.z != 0 ) ? z / other.z : FLT_MAX
	);
}

Vector3
Vector3::operator/( const f32 value ) const
{
	if ( value == 0 )
		return Vector3( FLT_MAX, FLT_MAX, FLT_MAX );

	return Vector3(
		x / value, y / value, z / value
	);
}

const Vector3::VectorProxy
Vector3::operator[]( const u32 index ) const
{
	BK_ASSERT( index < 3 && index >= 0, "index out of bounds." );
	return VectorProxy( (Vector<f32, 3>&)*this, index );
}

Vector3::VectorProxy
Vector3::operator[]( const u32 index )
{
	BK_ASSERT( index < 3 && index >= 0, "index out of bounds." );
	return VectorProxy( *this, index );
}

f32
Vector3::mag() const
{
	return sqrt( x * x + y * y + z * z );
}

f32
Vector3::magSqr() const
{
	return dot( *this );
}

Vector3
Vector3::normalised() const
{
	f32 rev = 1 / mag();
	return Vector3( x * rev, y * rev, z * rev );
}

Vector3&
Vector3::normalise()
{
	f32 rev = 1 / mag();

	x = x * rev;
	y = y * rev;
	z = z * rev;

	return *this;
}

f32
Vector3::dot( const Vector3 &other ) const
{
	return ( x * other.x + y * other.y + z * other.z );
}

Vector3
Vector3::cross( const Vector3 &other ) const
{
	return Vector3{
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}

