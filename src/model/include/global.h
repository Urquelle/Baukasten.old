#ifndef GLOBAL_H
#define GLOBAL_H

#include <list>
#include <map>
#include <memory>
#include <string>

using namespace std;

namespace Baukasten {
	class Action;
	class Drawable;
	class Entity;
	class EntityType;
	class GameEntity;
	class LogicalSpace;
	class State;
	class VirtualSpace;

	enum Dim {
		BK_X = 0, BK_WIDTH = 0,
		BK_Y = 1, BK_HEIGHT = 1,
		BK_Z, BK_W
	};

	using namespace std;

	typedef map<string, shared_ptr<Entity>>	EntityMap;
	typedef list<shared_ptr<Entity>>		EntityList;

	typedef map<string, shared_ptr<EntityType>> EntityTypeMap;
	typedef list<shared_ptr<EntityType>>	EntityTypeList;

	typedef map<string, shared_ptr<GameEntity>> GameEntityMap;
	typedef list<shared_ptr<GameEntity>>	GameEntityList;

	typedef map<string, shared_ptr<Action>>	ActionMap;
	typedef list<shared_ptr<Action>>		ActionList;

	typedef map<string, LogicalSpace*>		LSpaces;
	typedef map<string, shared_ptr<VirtualSpace>> VSpaces;

	typedef map<string, shared_ptr<State>>	StateMap;
	typedef list<shared_ptr<State>>			StateList;
}

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif // GLOBAL_H

