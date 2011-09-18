#include "gameentity_manager.h"

#include "game_entity.h"
#include "debug.h"

using namespace Baukasten;

GameEntityManager::GameEntityManager()
{
}

GameEntityManager::~GameEntityManager()
{
}

void GameEntityManager::addGameEntity( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	add( entity );
}

void GameEntityManager::addGameEntity(
	const std::string &id, GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	add( id, entity );
}

GameEntity* GameEntityManager::getGameEntity(
	const std::string &id ) const
{
	return get( id );
}

AbstractManager<GameEntity>::TMap
GameEntityManager::getGameEntities() const
{
	return getAll();
}

bool GameEntityManager::hasGameEntity( const std::string &id ) const
{
	return has( id );
}

void GameEntityManager::removeGameEntity( const std::string &id )
{
	remove( id );
}

