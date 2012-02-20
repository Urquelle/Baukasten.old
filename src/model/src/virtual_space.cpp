#include "model/VirtualSpace"

#include "core/Debug"
#include "model/Form"

using namespace Baukasten;

VirtualSpace::VirtualSpace()
{
}

VirtualSpace::~VirtualSpace()
{
}

Form*
VirtualSpace::entity( const std::string &id ) const
{
	auto it = m_map.find( id );
	if ( it == m_map.end() )
		return 0;

	return it->second;
}

void
VirtualSpace::addEntity( const string &id, Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	BK_ASSERT(
		!hasEntity( id ),
		"id " << id << " must be unique in the collection."
	);

	m_map[ id ] = entity;
	m_list.push_back( entity );
}

void
VirtualSpace::addEntity( Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	BK_ASSERT(
		!hasEntity( entity->id() ),
		"id " << entity->id() << " must be unique in the collection."
	);

	addEntity( entity->id(), entity );
}

list<Form*>
VirtualSpace::entities() const
{
	return m_list;
}

bool
VirtualSpace::hasEntity( const string &id ) const
{
	return m_map.count( id );
}

void
VirtualSpace::removeEntity( const string &id )
{
	m_map.erase( m_map.find( id ) );
	m_list.remove_if( [&id]( Form *form ) {
		return form->id() == id;
	});
}

