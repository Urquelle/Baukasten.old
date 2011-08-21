#ifndef GLOBAL_LUA_S7HRAEG3
#define GLOBAL_LUA_S7HRAEG3

#include <global.h>
#include <entity.h>
#include <entity_type.h>
#include <game_entity.h>
#include <generic_state.h>
#include <state.h>

#include "slb/SLB.hpp"

void wrapClasses()
{
	using namespace Baukasten::Core;

	// register Entity Class
	SLB::Class<Entity>("Entity")
		.comment("Wrapper for the Entity Class.")
		.constructor<const std::string&>()
		.const_set("getId", &Entity::getId);

	// register IncStates Class
	SLB::Class<IncStates>("IncStates")
		.comment("IncStates Wrapper.")
		.constructor()
		.set("addState", &IncStates::addState)
			.param("State object.")
		.set("getState", &IncStates::getState);

	SLB::Class<Action,SLB::Instance::NoCopy>("Action")
		.comment("Action Wrapper")
		.inherits<Entity>()
		.set("getSource", &Action::getSource)
		.set("clear", &Action::clear)
		.set("isActive", &Action::isActive)
		.set("setActive", &Action::setActive)
			.param("bool to indicate whether the action should stay in the queue")
		.set("setTarget", &Action::setTarget)
			.param("GameEntity as the target")
		.set("getTarget", &Action::getTarget);

	// register the ActionLua Class
	SLB::Class<ActionLua>("ActionLua")
		.comment("ActionLua Wrapper")
		.constructor<GameEntity&, const std::string&, const std::string&>()
		.inherits<Action>()
		.inherits<Entity>()
		.set("doAction", &ActionLua::doAction)
			.param("GameEntity as the target Object.");

	// register EntityType Class
	SLB::Class<EntityType>("EntityType")
		.comment("Wrapper for the EntityTypeClass.")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.inherits<IncStates>()
		.set("setParent", &EntityType::setParent)
			.param("EntityType as objects parent")
		.const_set("getParent", &EntityType::getParent)
		.set("addChild", &EntityType::addChild)
			.param("EntityType as objects child.")
		.set("removeChild", &EntityType::removeChild)
		.const_set("getState", &EntityType::getState)
			.param("State ID")
		.set("getEntityState", &EntityType::getEntityState);

	// register GameEntity Class
	SLB::Class<GameEntity>("GameEntity")
		.comment("Wrapper for the GameEntity Class.")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.set("setType", &GameEntity::setType)
			.param("the EntityType.")
		.set("getType", &GameEntity::getType)
		.set("hasState", &GameEntity::hasState)
			.param("state id")
		.set("getState", &GameEntity::getState)
			.param("state id");

	// register State Class
	SLB::Class<State>("State")
		.comment("Wrapper for the State Class.")
		.constructor<const std::string&>()
		.inherits<Entity>();

	// register GenericState with int as the template argument
	SLB::Class<GenericState<int> >("StateInt")
		.comment("Wrapper for the StateInt Class.")
		.constructor<const std::string&>()
		.inherits<State>()
		.set("setValue",&StateInt::setValue)
			.param("expects an integer.")
		.set("getValue",&StateInt::getValue);
}

#endif /* end of include guard: GLOBAL_LUA_S7HRAEG3 */

