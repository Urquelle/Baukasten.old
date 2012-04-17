#include "math/include/vector3.h"

#include "core/Assert"

#include <cfloat>
#include <cmath>

using namespace Baukasten;
using namespace std;

Vector3::Vector3() :
	//(*this){ 0.0, 0.0, 0.0 },
	Vector(),
	m_mag( -1.0 )
{
}

Vector3::Vector3( const Vector3 &other ) :
	Vector({ other[0], other[1], other[2] }),
	m_mag( -1.0 )
{
}

Vector3::Vector3( const f32 value ) :
	Vector({ value, value, value }),
	m_mag( -1.0 )
{
}

Vector3::Vector3( const f32 _f, const f32 _s, const f32 _t ) :
	Vector({ _f, _s, _t }),
	m_mag( -1.0 )
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
	m_dirty = true;
	return *this;
}

Vector3&
Vector3::operator=( const f32 value )
{
	Type::operator=({ value, value, value });
	m_dirty = true;
	return *this;
}

bool
Vector3::operator==( const Vector3 &other ) const
{
	f32 tolerance = 0.00000001;

	if (
		fabs( (*this)[0] - other[0] ) < tolerance &&
		fabs( (*this)[1] - other[1] ) < tolerance &&
		fabs( (*this)[2] - other[2] ) < tolerance
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
	return Vector3( (*this)[0] + other[0], (*this)[1] + other[1],
		(*this)[2] + other[2] );
}

Vector3
Vector3::operator+( const f32 value ) const
{
	return Vector3( (*this)[0] + value, (*this)[1] + value,
		(*this)[2] + value );
}

Vector3
Vector3::operator*( const Vector3 &other ) const
{
	return Vector3( (*this)[0] * other[0], (*this)[1] * other[1],
		(*this)[2] * other[2] );
}

Vector3
Vector3::operator*( const f32 value ) const
{
	return Vector3( (*this)[0] * value, (*this)[1] * value,
		(*this)[2] * value );
}

Vector3
Vector3::operator/( const Vector3 &other ) const
{
	return Vector3(
		( other[0] != 0 ) ? (*this)[0] / other[0] : FLT_MAX,
		( other[1] != 0 ) ? (*this)[1] / other[1] : FLT_MAX,
		( other[2] != 0 ) ? (*this)[2] / other[2] : FLT_MAX
	);
}

Vector3
Vector3::operator/( const f32 value ) const
{
	if ( value == 0 )
		return Vector3( FLT_MAX, FLT_MAX, FLT_MAX );

	return Vector3(
		(*this)[0] / value, (*this)[1] / value, (*this)[2] / value
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
	if ( m_mag < 0 || m_dirty ) {
		m_mag = sqrt(
			(*this)[0] * (*this)[0] +
			(*this)[1] * (*this)[1] +
			(*this)[2] * (*this)[2]
		);
		m_dirty = false;
	}

	return m_mag;
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
	return Vector3(
		(*this)[0] * rev,
		(*this)[1] * rev,
		(*this)[2] * rev
	);
}

Vector3&
Vector3::normalise()
{
	f32 rev = 1 / mag();

	(*this)[0] = (*this)[0] * rev;
	(*this)[1] = (*this)[1] * rev;
	(*this)[2] = (*this)[2] * rev;

	m_dirty = true;

	return *this;
}

f32
Vector3::dot( const Vector3 &other ) const
{
	return (
		(*this)[0] * other[0] +
		(*this)[1] * other[1] +
		(*this)[2] * other[2]
	);
}

Vector3
Vector3::cross( const Vector3 &other ) const
{
	return Vector3{
		(*this)[1] * other[2] - (*this)[2] * other[1],
		(*this)[2] * other[0] - (*this)[0] * other[2],
		(*this)[0] * other[1] - (*this)[1] * other[0]
	};
}

