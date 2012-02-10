#include "core/Entity"

#include "core/Debug"
#include "core/State"

using namespace Baukasten;

Entity::Entity( const std::string &id ) :
	mId( id )
{
}

Entity::~Entity()
{
	BK_DEBUG( getId() + " destroyed." );
}

Entity&
Entity::operator=( const Entity &other )
{
	if ( this == &other )
		return *this;

	mId = other.getId();

	return *this;
}

bool
Entity::operator==( const Entity &other ) const
{
	return ( getId() == other.getId() );
}

const std::string&
Entity::getId() const
{
	return mId;
}

