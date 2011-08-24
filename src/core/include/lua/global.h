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
	using namespace Baukasten;

	// register Entity Class
	SLB::Class<Entity>("Entity")
		.comment("Wrapper for the Entity Class.")
		.constructor<const std::string&>()
		.const_set("getId", &Entity::getId);

	// register StateManager Class
	SLB::Class<StateManager>("StateManager")
		.comment("StateManager Wrapper.")
		.constructor()
		.set("addState", ( void (StateManager::*)(State*) ) &StateManager::addState)
			.param("State Object")
		.set("addState", ( void (StateManager::*)(const std::string&, State*) ) &StateManager::addState)
			.param("ID of the State")
			.param("State Object")
		.set("getState", &StateManager::getState<State*>);

	SLB::Class<ActionManager>("ActionManager")
		.comment("ActionManager Wrapper")
		.constructor()
		.set("addAction", ( void (ActionManager::*)(Action*) ) &ActionManager::addAction)
			.param("Action Object")
		.set("addAction", ( void (ActionManager::*)(const std::string&, Action*) ) &ActionManager::addAction)
			.param("ID of the Action")
			.param("Action Object")
		.set("getAction", &ActionManager::getAction)
			.param("ID of the Action")
		.set("getActions", &ActionManager::getActions)
			.comment("Returns a Map of assigned Actions.")
		.set("hasAction", &ActionManager::hasAction)
			.param("ID of the Action to look for")
		.set("invokeAction", ( void (ActionManager::*)(const std::string&) ) &ActionManager::invokeAction)
			.param("State Object")
		.set("invokeActionOnTarget", ( void (ActionManager::*)(const std::string&, GameEntity*) ) &ActionManager::invokeAction)
			.param("ID of the Action")
			.param("Target Object")
		.set("invokeActionOnTargets", ( void (ActionManager::*)(const std::string&, GameEntityList) ) &ActionManager::invokeAction)
			.param("ID of the Action")
			.param("Target List")
		.set("dropAction", &ActionManager::dropAction)
			.param("ID of the Action to drop from the execution queue")
		.set("runActions", &ActionManager::runActions);

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
		.inherits<StateManager>()
		.set("setParent", &EntityType::setParent)
			.param("EntityType as objects parent")
		.const_set("getParent", &EntityType::getParent)
		.set("addChild", &EntityType::addChild)
			.param("EntityType as objects child.")
		.set("removeChild", &EntityType::removeChild)
		.const_set("getState", &EntityType::getState<State*>)
			.param("State ID")
		.set("getEntityState", &EntityType::getEntityState);

	// register GameEntity Class
	SLB::Class<GameEntity>("GameEntity")
		.comment("Wrapper for the GameEntity Class.")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.inherits<StateManager>()
		.inherits<ActionManager>()
		.set("setType", &GameEntity::setType)
			.param("the EntityType.")
		.set("getType", &GameEntity::getType)
		.set("hasState", &GameEntity::hasState)
			.param("state id")
		.set("getState", &GameEntity::getState<State*>)
			.param("state id");

	// register State Class
	SLB::Class<State>("State")
		.comment("Wrapper for the State Class.")
		.constructor<const std::string&>()
		.inherits<Entity>();

	// register GenericState with int as the template argument
	SLB::Class<StateInt>("StateInt")
		.comment("Wrapper for the StateInt Class.")
		.constructor<const std::string&>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateInt::setValue)
			.param("expects an integer.")
		.set("getValue",&StateInt::getValue);

	// register GenericState with string as the template argument
	SLB::Class<StateString>("StateString")
		.comment("Wrapper for the StateString Class.")
		.constructor<const std::string&>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateString::setValue)
			.param("expects a string.")
		.set("getValue",&StateString::getValue);
}

#endif /* end of include guard: GLOBAL_LUA_S7HRAEG3 */

