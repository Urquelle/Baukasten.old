#include "model/EntityManager"

#include "core/Debug"
#include "model/Entity"

using namespace Baukasten;

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void
EntityManager::addEntity( Entity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	add( entity );
}

void
EntityManager::addEntity( const string &id, Entity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	add( id, entity );
}

Entity*
EntityManager::entity( const string &id ) const
{
	return get( id );
}

EntityManager::TMap
EntityManager::entities() const
{
	return all();
}

bool
EntityManager::hasEntity( const string &id ) const
{
	return has( id );
}

void
EntityManager::removeEntity( const string &id )
{
	remove( id );
}

