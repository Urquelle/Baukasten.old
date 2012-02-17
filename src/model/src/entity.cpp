#include "model/Entity"

#include "model/Debug"
#include "model/State"

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

string
Entity::id() const
{
	return mId;
}
