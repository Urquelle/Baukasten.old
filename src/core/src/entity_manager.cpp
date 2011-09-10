#include "entity_manager.h"

#include "entity.h"
#include "debug.h"

using namespace Baukasten;

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity( Entity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	add( entity );
}

void EntityManager::addEntity( const std::string &id, Entity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	add( id, entity );
}

Entity* EntityManager::getEntity( const std::string &id ) const
{
	return get( id );
}

EntityMap EntityManager::getEntities() const
{
	return getAll();
}

bool EntityManager::hasEntity( const std::string &id ) const
{
	return has( id );
}

void EntityManager::removeEntity( const std::string &id )
{
	remove( id );
}

