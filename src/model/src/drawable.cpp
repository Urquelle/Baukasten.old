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
	mPosition = position;
}

const vec3<float>
Drawable::position() const
{
	return mPosition;
}

void
Drawable::setSize( const vec2<float> size )
{
	mSize = size;
}

const vec2<float>
Drawable::size() const
{
	return mSize;
}

void
Drawable::setPitch( const float pitch )
{
	mPitch = pitch;
}

const
float Drawable::pitch() const
{
	return mPitch;
}

void
Drawable::setYaw( const float yaw )
{
	mYaw = yaw;
}

const float
Drawable::yaw() const
{
	return mYaw;
}

void
Drawable::setRoll( const float roll )
{
	mRoll = roll;
}

const float
Drawable::roll() const
{
	return mRoll;
}

void
Drawable::setScale( const float scale )
{
	mScale = scale;
}

const float
Drawable::scale() const
{
	return mScale;
}

void
Drawable::setVisible( bool visible )
{
}

