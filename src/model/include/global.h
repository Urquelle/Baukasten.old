#ifndef GLOBAL_H
#define GLOBAL_H

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Baukasten {

	typedef  signed    char  s8;
	typedef  unsigned  char  u8;
	typedef  signed    short s16;
	typedef  unsigned  short u16;
	typedef  signed    int   u32;
	typedef  unsigned  int   s32;

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

#define BK_PIMPL_PTR( Class ) \
	friend class Class##Private; \
	Class##Private* mImpl

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif // GLOBAL_H

