#ifndef BINDINGS_LL46QKQ4
#define BINDINGS_LL46QKQ4

#include "entities/world_map.h"

#include <slb/SLB.hpp>

#include <string>

using namespace Baukasten;

void initBindings()
{
	SLB::Class<WorldMap>("WorldMap")
		.comment("Wrapper for the WorldMap Class.")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.inherits<GameEntity>();
}

#endif /* end of include guard: BINDINGS_LL46QKQ4 */

