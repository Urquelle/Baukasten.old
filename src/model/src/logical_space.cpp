#include "model/LogicalSpace"

#include "model/GameEntity"

#include <algorithm>

using namespace Baukasten;

LogicalSpace::LogicalSpace()
{
}

LogicalSpace::~LogicalSpace()
{
}

GameEntity*
LogicalSpace::entity( const string &id ) const
{
	auto it = m_map.find( id );
	if ( it == m_map.end() )
		return 0;

	return it->second;
}

void
LogicalSpace::runActions()
{
	for( GameEntity *entity : m_list ) {
		entity->runActions();
	}
}

void
LogicalSpace::addEntity( const string &id, GameEntity *entity )
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
LogicalSpace::addEntity( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	addEntity( entity->id(), entity );
}

list<GameEntity*>
LogicalSpace::entities() const
{
	return m_list;
}

bool
LogicalSpace::hasEntity( const string &id ) const
{
	return m_map.count( id );
}

void
LogicalSpace::removeEntity( const string &id )
{
	m_map.erase( m_map.find( id ) );
	m_list.remove_if( [&id]( GameEntity *entity ) {
		return entity->id() == id;
	});
}

