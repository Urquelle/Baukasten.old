#include "logical_space.h"

#include "game_entity.h"

using namespace Baukasten;

LogicalSpace::LogicalSpace() :
	EntityManager()
{
}

LogicalSpace::~LogicalSpace()
{
}

void LogicalSpace::runActions()
{
	auto map = getEntities();
	auto it = map.begin();
	while ( it != map.end() ) {
		( static_cast<GameEntity*>( it->second.get() ) )->runActions();
		it++;
	}
}
