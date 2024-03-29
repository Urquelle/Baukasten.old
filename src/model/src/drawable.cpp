#include "model/Drawable"

using namespace Baukasten;

Drawable::Drawable( const string &id ) :
	Entity( id )
{
}

Drawable::~Drawable()
{
}

void
Drawable::setPosition( const Vector3 position )
{
	m_position = position;
}

const Vector3
Drawable::position() const
{
	return m_position;
}

void
Drawable::setSize( const Vector2 size )
{
	m_size = size;
}

const Vector2
Drawable::size() const
{
	return m_size;
}

void
Drawable::setPitch( const f32 pitch )
{
	m_pitch = pitch;
}

const f32
Drawable::pitch() const
{
	return m_pitch;
}

void
Drawable::setYaw( const f32 yaw )
{
	m_yaw = yaw;
}

const f32
Drawable::yaw() const
{
	return m_yaw;
}

void
Drawable::setRoll( const f32 roll )
{
	m_roll = roll;
}

const f32
Drawable::roll() const
{
	return m_roll;
}

void
Drawable::setScale( const f32 scale )
{
	m_scale = scale;
}

const f32
Drawable::scale() const
{
	return m_scale;
}

