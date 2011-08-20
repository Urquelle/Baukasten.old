#ifndef GLOBAL_LUA_S7HRAEG3
#define GLOBAL_LUA_S7HRAEG3

#include "global.h"
#include "game_entity.h"
#include "generic_state.h"
#include "state.h"

#include "slb/SLB.hpp"

void wrapClasses()
{
	using namespace Baukasten::Core;

	SLB::Class<Object>("Object")
		.constructor<const std::string&>()
		.const_set("getId", &Object::getId);


	SLB::Class<Entity>("Entity")
		.comment("Wrapper for the Entity Class.")
		.constructor<const std::string&>()
		.inherits<Object>()
		.set("addState", &Entity::addState)
			.param("receives a State Object.")
		.set("getState", &Entity::getState)
			.param("String as the id of the State");

	SLB::Class<GameEntity>("GameEntity")
		.comment("Wrapper for the GameEntity Class.")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.set("hasState", &GameEntity::hasState)
			.param("id of the state")
		.set("getId", &GameEntity::getId)
			.comment("Returns the id");

	SLB::Class<State>("State")
		.comment("Wrapper for the State Class.")
		.constructor<const std::string&>();

	SLB::Class<GenericState<int>>("StateInt")
		.comment("Wrapper for the StateInt Class.")
		.constructor<const std::string&>()
		.inherits<State>()
		.set("setValue",&StateInt::setValue)
			.param("expects an integer.")
		.set("getValue",&StateInt::getValue);
}

#endif /* end of include guard: GLOBAL_LUA_S7HRAEG3 */

