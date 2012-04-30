#include "math/include/quaternion.h"

namespace Baukasten {

Quaternion::Quaternion() :
	Vector(),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] ), w( m_data[3] )
{
}

Quaternion::Quaternion( const f32 x, const f32 y,
		const f32 z, const f32 w ) :
	Vector({ x, y, z, w }),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] ), w( m_data[3] )
{
}

Quaternion::Quaternion( const f32 *values ) :
	Vector({ values[0], values[1], values[2], values[3] }),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] ), w( m_data[3] )
{
}

Quaternion::Quaternion( const Quaternion &other ) :
	Vector({ other.x, other.y, other.z, other.w }),
	x( m_data[0] ), y( m_data[1] ), z( m_data[2] ), w( m_data[3] )
{
}

Quaternion::~Quaternion()
{
}

Quaternion&
Quaternion::operator=( const Quaternion &other )
{
	if ( this == &other )
		return *this;

	Type::operator=( other );
	return *this;
}

const Quaternion::VectorProxy
Quaternion::operator[]( const u32 index ) const
{
	BK_ASSERT( index < 4 && index >= 0, "index out of bounds." );
	return VectorProxy( (Vector<f32, 4>&)*this, index );
}

Quaternion::VectorProxy
Quaternion::operator[]( const u32 index )
{
	BK_ASSERT( index < 4 && index >= 0, "index out of bounds." );
	return VectorProxy( *this, index );
}

}

