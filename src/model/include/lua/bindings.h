#ifndef GLOBAL_LUA_S7HRAEG3
#define GLOBAL_LUA_S7HRAEG3

#include "model/Global"

#include "graphics/IGraphics"
#include "model/Model"

#include "model/include/slb/SLB.hpp"

void wrapClasses()
{
	using namespace Baukasten;

	// register Entity class
	SLB::Class<Entity>("Entity")
		.comment("Wrapper for the Entity Class.")
		.constructor<const std::string&>()
		.const_set("id", &Entity::id);

	// register Drawable class
	SLB::Class<Drawable,SLB::Instance::NoCopy>("Drawable")
		.comment("Drawable class")
		.inherits<Entity>()
		.set("setPosition", &Drawable::setPosition)
			.param("position")
		.set("position", &Drawable::position)
		.set("setSize", &Drawable::setSize)
			.param("size")
		.set("size", &Drawable::size)
		.set("setPitch", &Drawable::setPitch)
			.param("float value")
		.const_set("pitch", &Drawable::pitch)
		.set("setYaw", &Drawable::setYaw)
			.param("float value")
		.const_set("yaw", &Drawable::yaw)
		.set("setRoll", &Drawable::setRoll)
			.param("float value")
		.const_set("roll", &Drawable::roll)
		.set("setScale", &Drawable::setScale)
			.param("float value")
		.const_set("scale", &Drawable::scale)
		.set("setVisible", &Drawable::setVisible)
			.param("bool value to set the visibility");

	// register EntityManager class
	SLB::Class<EntityManager>("EntityManager")
		.comment("EntityManager class")
		.constructor()
		.set("addEntity", ( void (EntityManager::*)(Entity*) ) &EntityManager::addEntity)
			.param("Entity object")
		.set("entity", &EntityManager::entity)
			.param("Entity id")
		.const_set("entities", &EntityManager::entities)
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
		.const_set("state", &StateManager::state<State*>)
		.const_set("states", &StateManager::states)
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
		.set("action", &ActionManager::action)
			.param("ID of the Action")
		.set("actions", &ActionManager::actions)
			.comment("Returns a Map of assigned Actions.")
		.set("hasAction", &ActionManager::hasAction)
			.param("ID of the Action to look for")
		.set("invokeAction", ( void (ActionManager::*)(const std::string&) ) &ActionManager::invokeAction)
			.param("State Object")
		.set("invokeActionOnTarget", ( void (ActionManager::*)(const std::string&, GameEntity*) ) &ActionManager::invokeAction)
			.param("ID of the Action")
			.param("Target Object")
		.set("invokeActionOnTargets", ( void (ActionManager::*)(const std::string&, list<GameEntity*>) ) &ActionManager::invokeAction)
			.param("ID of the Action")
			.param("Target List")
		.set("dropAction", &ActionManager::dropAction)
			.param("ID of the Action to drop from the execution queue");

	// register Action class
	SLB::Class<Action,SLB::Instance::NoCopy>("Action")
		.comment("Action Wrapper")
		.inherits<Entity>()
		.set("source", &Action::source)
		.set("clear", &Action::clear)
		.set("isActive", &Action::isActive)
		.set("setActive", &Action::setActive)
			.param("bool to indicate whether the action should stay in the queue")
		.set("setTarget", &Action::setTarget)
			.param("GameEntity as the target")
		.set("target", &Action::target);

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
		.const_set("parent", &EntityType::parent)
		.set("addChild", &EntityType::addChild)
			.param("EntityType as objects child.")
		.set("removeChild", &EntityType::removeChild)
		.set("state", &EntityType::state<State*>)
			.param("State ID")
		.set("entityState", &EntityType::entityState);

	// register GameEntity Class
	SLB::Class<GameEntity>("GameEntity")
		.comment("Wrapper for the GameEntity Class.")
		.constructor<const std::string&>()
		.inherits<Entity>()
		.set("setType", &GameEntity::setType)
			.param("the EntityType.")
		.set("type", &GameEntity::type)
		.set("hasState", &GameEntity::hasState)
			.param("state id")
		.set("state", &GameEntity::state<State*>)
			.param("state id")
		.set("parent", &GameEntity::parent)
		.set("child", &GameEntity::child)
			.param("child id")
		.const_set("children", &GameEntity::children)
		.set("addChild", ( void (GameEntity::*)(GameEntity*) ) &GameEntity::addChild)
			.param("gameentity object")
		.set("addChild", ( void (GameEntity::*)(const std::string&, GameEntity*) ) &GameEntity::addChild)
			.param("child id")
			.param("gameentity object")
		.set("form", &GameEntity::form)
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
		.set("value",&StateInt::value);

	// register GenericState with string as the template argument
	SLB::Class<StateString>("StateString")
		.comment("Wrapper for the StateString Class.")
		.constructor<const std::string&>()
		.constructor<const std::string&, std::string>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateString::setValue)
			.param("expects a string.")
		.set("value",&StateString::value);

	// register GenericState with boolean as the template argument
	SLB::Class<StateBool>("StateBool")
		.comment("Wrapper for the StateBool Class.")
		.constructor<const std::string&>()
		.constructor<const std::string&, bool>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateBool::setValue)
			.param("expects a boolean.")
		.set("value",&StateBool::value);

	SLB::Class<StateIntVector>("StateIntVector")
		.comment("Wrapper for the StateIntVector Class.")
		.constructor<const std::string&>()
		.constructor<const std::string&, vector<int>>()
		.inherits<State>()
		.inherits<Entity>()
		.set("setValue",&StateIntVector::setValue)
			.param("index int value")
			.param("int value")
		.set("setValues", ( void (StateIntVector::*)(StateIntVector*) ) &StateIntVector::setValues)
			.param("values")
		.set("value",&StateIntVector::value)
			.param("index int value");

	// register Form class
	SLB::Class<Form>("Form")
		.comment("Form class")
		.constructor<const std::string&, IGraphics*>()
		.inherits<Entity>()
		.inherits<Drawable>()
		.inherits<StateManager>()
		.inherits<EntityManager>()
		.set("addToLSpace", ( void (Form::*)(GameEntity*) ) &Form::addToLSpace)
			.param("Entity expected")
		.set("addToLSpace", ( void (Form::*)(const std::string&, GameEntity*) ) &Form::addToLSpace)
			.param("Entity id")
			.param("Entity object")
		.set("removeFromLSpace", &Form::removeFromLSpace)
			.param("Entity id expected")
		.set("lSpace", &Form::lSpace)
		.set("addToVSpace", ( void (Form::*)(Form*) ) &Form::addToVSpace)
			.param("Entity expected")
		.set("addToVSpace", ( void (Form::*)(const std::string&, Form*) ) &Form::addToVSpace)
			.param("Entity id")
			.param("Entity object")
		.set("removeFromVSpace", &Form::removeFromVSpace)
			.param("Entity id expected")
		.set("vSpace", &Form::vSpace);

	// register LogicalSpace class
	SLB::Class<LogicalSpace>("LogicalSpace")
		.comment("LogicalSpace class")
		.constructor()
		.set("entity", &LogicalSpace::entity)
			.param("Entity id");

	// register VirtualSpace class
	SLB::Class<VirtualSpace>("VirtualSpace")
		.comment("VirtualSpace class")
		.constructor()
		.set("entity", &VirtualSpace::entity)
			.param("Entity id");

	// register vec3<float> struct
	SLB::Class<vec3<float>>("vec3<float>")
		.comment("vec3<float> struct")
		.constructor()
		.constructor<float, float, float>()
		.set("x", &vec3<float>::first)
		.set("y", &vec3<float>::second)
		.set("z", &vec3<float>::third);
}

#endif /* end of include guard: GLOBAL_LUA_S7HRAEG3 */

