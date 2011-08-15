#include "drawable.h"

using namespace Baukasten::Core;

Drawable::Drawable() :
    Entity()
{
}

Drawable::Drawable( const std::string &id ) :
    Entity( id )
{
}

void Drawable::setPosition( const t_pos position )
{
    mPosition = position;
}

const t_pos Drawable::getPosition() const
{
    return mPosition;
}

void Drawable::setPitch( const float pitch )
{
    mPitch = pitch;
}

const float Drawable::getPitch() const
{
    return mPitch;
}

void Drawable::setYaw( const float yaw )
{
    mYaw = yaw;
}

const float Drawable::getYaw() const
{
    return mYaw;
}

void Drawable::setRoll( const float roll )
{
    mRoll = roll;
}

const float Drawable::getRoll() const
{
    return mRoll;
}

void Drawable::setScale( const float scale )
{
    mScale = scale;
}

const float Drawable::getScale() const
{
    return mScale;
}

