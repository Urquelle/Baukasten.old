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
	BK_DEBUG( id() + " destroyed." );
}

Entity&
Entity::operator=( const Entity &other )
{
	if ( this == &other )
		return *this;

	mId = other.id();

	return *this;
}

bool
Entity::operator==( const Entity &other ) const
{
	return ( id() == other.id() );
}

const std::string&
Entity::id() const
{
	return mId;
}

