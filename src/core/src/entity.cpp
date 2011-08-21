#include "entity.h"
#include "state.h"

using namespace Baukasten::Core;

Entity::Entity( const std::string &id ) :
	mId( id )
{
}

Entity::~Entity()
{
}

Entity& Entity::operator=( const Entity &other )
{
	if ( this == &other )
		return *this;

	mId = other.getId();

	return *this;
}

bool Entity::operator==( const Entity &other ) const
{
	return ( getId() == other.getId() );
}

const std::string Entity::getId() const
{
	return mId;
}

