#include "math/include/vector2.h"

#include "core/Assert"

#include <cfloat>
#include <cmath>

using namespace Baukasten;
using namespace std;

Vector2::Vector2() :
	Vector(),
	x( m_data[0] ), y( m_data[1] )
{
}

Vector2::Vector2( const Vector2 &other ) :
	Vector({ other[ 0 ], other[ 1 ] }),
	x( m_data[0] ), y( m_data[1] )
{
}

Vector2::Vector2( const f32 value ) :
	Vector({ value, value }),
	x( m_data[0] ), y( m_data[1] )
{
}

Vector2::Vector2( const f32 _f, const f32 _s ) :
	Vector({ _f, _s }),
	x( m_data[0] ), y( m_data[1] )
{
}

Vector2::~Vector2()
{
}

Vector2&
Vector2::operator=( const Vector2 &other )
{
	if ( this == &other )
		return *this;

	Type::operator=( other );
	return *this;
}

Vector2&
Vector2::operator=( const f32 value )
{
	Type::operator=({ value, value });
	return *this;
}

bool
Vector2::operator==( const Vector2 &other ) const
{
	if (
		fabs( x - other.x ) < BK_MATH_EPSILON &&
		fabs( y - other.y ) < BK_MATH_EPSILON
	) return true;

	return false;
}

bool
Vector2::operator!=( const Vector2 &other ) const
{
	return !operator==( other );
}

Vector2
Vector2::operator+( const Vector2 &other ) const
{
	return Vector2( x + other.x, y + other.y );
}

Vector2
Vector2::operator+( const f32 value ) const
{
	return Vector2( x + value, y + value );
}

Vector2
Vector2::operator*( const Vector2 &other ) const
{
	return Vector2( x * other.x, y * other.y );
}

Vector2
Vector2::operator*( const f32 value ) const
{
	return Vector2( x * value, y * value );
}

Vector2
Vector2::operator/( const Vector2 &other ) const
{
	return Vector2(
		( other.x != 0 ) ? x / other.x : FLT_MAX,
		( other.y != 0 ) ? y / other.y : FLT_MAX
	);
}

Vector2
Vector2::operator/( const f32 value ) const
{
	if ( value == 0 )
		return Vector2( FLT_MAX, FLT_MAX );

	return Vector2( x / value, y / value );
}

const Vector2::VectorProxy
Vector2::operator[]( const u32 index ) const
{
	BK_ASSERT( index < 2 && index >= 0, "index out of bounds." );
	return VectorProxy( (Vector<f32, 2>&)*this, index );
}

Vector2::VectorProxy
Vector2::operator[]( const u32 index )
{
	BK_ASSERT( index < 2 && index >= 0, "index out of bounds." );
	return VectorProxy( *this, index );
}

f32
Vector2::mag() const
{
	return sqrt( x * x + y * y );
}

f32
Vector2::magSqr() const
{
	return dot( *this );
}

Vector2
Vector2::normalised() const
{
	f32 rev = 1 / mag();
	return Vector2( x * rev, y * rev );
}

Vector2&
Vector2::normalise()
{
	f32 rev = 1 / mag();

	x *= rev;
	y *= rev;

	return *this;
}

f32
Vector2::dot( const Vector2 &other ) const
{
	return ( x * other.x + y * other.y );
}

