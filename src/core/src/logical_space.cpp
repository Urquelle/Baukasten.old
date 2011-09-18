#include "logical_space.h"

#include "game_entity.h"

#include <algorithm>

using namespace Baukasten;

LogicalSpace::LogicalSpace() :
	GameEntityManager()
{
}

LogicalSpace::~LogicalSpace()
{
}

void LogicalSpace::runActions()
{
	auto map = getGameEntities();
	for_each( map.begin(), map.end(), []( pair<string,shared_ptr<GameEntity>> entry ) {
		entry.second->runActions();
	});
}
