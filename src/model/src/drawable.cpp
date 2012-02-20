#include "model/Drawable"

using namespace Baukasten;

Drawable::Drawable( const std::string &id ) :
	Entity( id )
{
}

Drawable::~Drawable()
{
}

void
Drawable::setPosition( const vec3<float> position )
{
	m_position = position;
}

const vec3<float>
Drawable::position() const
{
	return m_position;
}

void
Drawable::setSize( const vec2<float> size )
{
	m_size = size;
}

const vec2<float>
Drawable::size() const
{
	return m_size;
}

void
Drawable::setPitch( const float pitch )
{
	m_pitch = pitch;
}

const
float Drawable::pitch() const
{
	return m_pitch;
}

void
Drawable::setYaw( const float yaw )
{
	m_yaw = yaw;
}

const float
Drawable::yaw() const
{
	return m_yaw;
}

void
Drawable::setRoll( const float roll )
{
	m_roll = roll;
}

const float
Drawable::roll() const
{
	return m_roll;
}

void
Drawable::setScale( const float scale )
{
	m_scale = scale;
}

const float
Drawable::scale() const
{
	return m_scale;
}

void
Drawable::setVisible( bool visible )
{
}

