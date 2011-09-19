#ifndef GLOBAL_LUA_S7HRAEG3
#define GLOBAL_LUA_S7HRAEG3

#include "global.h"

#include "action.h"
#include "action_lua.h"
#include "drawable.h"
#include "entity.h"
#include "entity_type.h"
#include "form.h"
#include "game_entity.h"
#include "generic_state.h"
#include "logical_space.h"
#include "state.h"
#include "virtual_space.h"

#include "slb/SLB.hpp"

void wrapClasses()
{
	using namespace Baukasten;

	// register Entity class
	SLB::Class<Entity>("Entity")
		.comment("Wrapper for the Entity Class.")
		.constructor<const std::string&>()
		.const_set("getId", &Entity::getId);

	// register Drawable class
	SLB::Class<Drawable,SLB::Instance::NoCopy>("Drawable")
		.comment("Drawable class")
		.inherits<Entity>()
		.set("setPosition", &Drawable::setPosition)
			.param("position")
		.set("getPosition", &Drawable::getPosition)
		.set("setSize", &Drawable::setSize)
			.param("size")
		.set("getSize", &Drawable::getSize)
		.set("setPitch", &Drawable::setPitch)
			.param("float value")
		.const_set("getPitch", &Drawable::getPitch)
		.set("setYaw", &Drawable::setYaw)
			.param("float value")
		.const_set("getYaw", &Drawable::getYaw)
		.set("setRoll", &Drawable::setRoll)
			.param("float value")
		.const_set("getRoll", &Drawable::getRoll)
		.set("setScale", &Drawable::setScale)
			.param("float value")
		.const_set("getScale", &Drawable::getScale)
		.set("setVisible", &Drawable::setVisible)
			.param("bool value to set the visibility");

	// register EntityManager class
	SLB::Class<EntityManager>("EntityManager")
		.comment("EntityManager class")
		.constructor()
		.set("addEntity", ( void (EntityManager::*)(Entity*) ) &EntityManager::addEntity)
			.param("Entity object")
		.set("getEntity", &EntityManager::getEntity)
			.param("Entity id")
		.const_set("getEntities", &EntityManager::getEntities)
		.const_set("hasEntity", &EntityManager::hasEntity)
		.set("removeEntity", &EntityManager::removeEntity)
			.param("Entity id");

	// register StateManager class
	SLB::Class<StateManager>("StateManager")
		.comment("StateManager Wrapper.")
		.constructor()
		.set("addState", ( void (StateManager::*)(State*) ) &StateManager::addState)
			.param("State Object")
		.set("addState", ( void (StateManager::*)(const std::string&, State*) ) &StateManager::addState)
			.param("ID of the State")
			.param("State Object")
		.const_set("getState", &StateManager::getState<State*>)
		.const_set("getStates", &StateManager::getStates)
		.const_set("hasState", &StateManager::hasState);

	// register ActionManager class
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
			.param("ID of the Action to drop from the execution queue");

	// register Action class
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
		.set("getState", &EntityType::getState<State*>)
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
			.param("state id")
		.set("getChild", &GameEntity::getChild)
			.param("child id")
		.set("addChild", &GameEntity::addChild)
			.param("gameentity object")
		.set("getForm", &GameEntity::getForm)
		.set("runActions", &GameEntity::runActions);

	// register State Class
	SLB::Class<State>("State")
		.comment("Wrapper for the State Class.")
		.constructor<const std::string&>()
		.inherits<Entity>();

	// register GenericState with int as the template argument
	SLB::Class<StateInt>("StateInt")
		.comment("Wrapper for the StateInt Class.")
		.constructor<const std::string&>()
		.constructor<const std::string&, int>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateInt::setValue)
			.param("expects an integer.")
		.set("getValue",&StateInt::getValue);

	// register GenericState with string as the template argument
	SLB::Class<StateString>("StateString")
		.comment("Wrapper for the StateString Class.")
		.constructor<const std::string&>()
		.constructor<const std::string&, std::string>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateString::setValue)
			.param("expects a string.")
		.set("getValue",&StateString::getValue);

	// register GenericState with boolean as the template argument
	SLB::Class<StateBool>("StateBool")
		.comment("Wrapper for the StateBool Class.")
		.constructor<const std::string&>()
		.constructor<const std::string&, bool>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateBool::setValue)
			.param("expects a boolean.")
		.set("getValue",&StateBool::getValue);

	// register Form class
	SLB::Class<Form>("Form")
		.comment("Form class")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.inherits<Drawable>()
		.inherits<StateManager>()
		.inherits<EntityManager>()
		.set("addToLSpace", &Form::addToLSpace)
			.param("Entity expected")
		.set("removeFromLSpace", &Form::removeFromLSpace)
			.param("Entity id expected")
		.set("getLSpace", &Form::getLSpace)
		.set("addToVSpace", &Form::addToVSpace)
			.param("Entity expected")
		.set("removeFromVSpace", &Form::removeFromVSpace)
			.param("Entity id expected")
		.set("getVSpace", &Form::getVSpace);

	// register LogicalSpace class
	SLB::Class<LogicalSpace>("LogicalSpace")
		.comment("LogicalSpace class")
		.constructor();

	// register VirtualSpace class
	SLB::Class<VirtualSpace>("VirtualSpace")
		.comment("VirtualSpace class")
		.constructor()
		.set("getEntity", &VirtualSpace::getEntity)
			.param("Entity id");

	// register t_pos struct
	SLB::Class<t_pos>("t_pos")
		.comment("t_pos struct")
		.constructor()
		.constructor<float, float, float>()
		.set("getX", &t_pos::getX)
		.set("setX", &t_pos::setX)
			.param("x value")
		.set("getY", &t_pos::getY)
		.set("setY", &t_pos::setY)
			.param("y value")
		.set("getZ", &t_pos::getZ)
		.set("setZ", &t_pos::setZ)
			.param("z value");
}

#endif /* end of include guard: GLOBAL_LUA_S7HRAEG3 */

