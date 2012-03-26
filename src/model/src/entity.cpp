#include "model/Entity"

#include "core/Debug"
#include "model/State"

using namespace Baukasten;

Entity::Entity( const string &id ) :
	m_id( id )
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

	m_id = other.id();

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
	return m_id;
}

