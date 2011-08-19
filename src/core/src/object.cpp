#include "object.h"

using namespace Baukasten::Core;

Object::Object( const std::string &id ) :
	mId( id )
{
}

Object::~Object()
{
}

void Object::operator=( const Object &other )
{
	mId = other.getId();
}

bool Object::operator==( const Object &other ) const
{
    return ( mId == other.getId() );
}

const std::string Object::getId() const
{
	return mId;
}

