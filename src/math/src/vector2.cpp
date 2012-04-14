#include "math/include/vector2.h"

#include "core/Assert"

#include <cfloat>
#include <cmath>

using namespace Baukasten;
using namespace std;

Vector2::Vector2() :
	m_data{ 0.0, 0.0 },
	m_mag( -1.0 )
{
}

Vector2::Vector2( const Vector2 &other ) :
	m_data{ other[0], other[1] },
	m_mag( -1.0 )
{
}

Vector2::Vector2( const f32 value ) :
	m_data{ value, value },
	m_mag( -1.0 )
{
}

Vector2::Vector2( const f32 _f, const f32 _s ) :
	m_data{ _f, _s },
	m_mag( -1.0 )
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

	m_data = { other[0], other[1] };
	m_dirty = true;
	return *this;
}

Vector2&
Vector2::operator=( const f32 value )
{
	m_data = { value, value };
	m_dirty = true;
	return *this;
}

bool
Vector2::operator==( const Vector2 &other ) const
{
	f32 tolerance = 0.00000001;

	if (
		fabs( m_data[0] - other[0] ) > tolerance &&
		fabs( m_data[1] - other[1] ) > tolerance
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
	return Vector2( m_data[0] + other[0], m_data[1] + other[1] );
}

Vector2
Vector2::operator+( const f32 value ) const
{
	return Vector2( m_data[0] + value, m_data[1] + value );
}

Vector2
Vector2::operator*( const Vector2 &other ) const
{
	return Vector2( m_data[0] * other[0], m_data[1] * other[1] );
}

Vector2
Vector2::operator*( const f32 value ) const
{
	return Vector2( m_data[0] * value, m_data[1] * value );
}

Vector2
Vector2::operator/( const Vector2 &other ) const
{
	return Vector2(
		( other[0] != 0 ) ? m_data[0] / other[0] : FLT_MAX,
		( other[1] != 0 ) ? m_data[1] / other[1] : FLT_MAX
	);
}

Vector2
Vector2::operator/( const f32 value ) const
{
	return Vector2(
		( value != 0 ) ? m_data[0] / value : FLT_MAX,
		( value != 0 ) ? m_data[1] / value : FLT_MAX
	);
}

f32
Vector2::operator[]( const u32 index ) const
{
	BK_ASSERT( index < 2 && index > 0, "index out of bounds." );
	return m_data[ index ];
}

f32
Vector2::mag() const
{
	if ( m_mag < 0 || m_dirty ) {
		m_mag = sqrt(
			m_data[0] * m_data[0] +
			m_data[1] * m_data[1]
		);
		m_dirty = false;
	}

	return m_mag;
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
	return Vector2(
		m_data[0] * rev,
		m_data[1] * rev
	);
}

Vector2&
Vector2::normalise()
{
	f32 rev = 1 / mag();

	m_data[0] *= rev;
	m_data[1] *= rev;

	m_dirty = true;

	return *this;
}

f32
Vector2::dot( const Vector2 &other ) const
{
	return (
		m_data[0] * other[0] +
		m_data[1] * other[1]
	);
}

