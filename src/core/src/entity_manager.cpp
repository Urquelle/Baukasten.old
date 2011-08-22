#include "entity_manager.h"

#include "entity.h"

using namespace Baukasten;

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void EntityManager::addEntity( const std::string &id, Entity *entity )
{
	add( entity );
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

