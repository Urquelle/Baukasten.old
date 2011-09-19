#ifndef GLOBAL_H
#define GLOBAL_H

#include <list>
#include <map>
#include <memory>
#include <string>

namespace Baukasten {
	class Action;
	class Drawable;
	class Entity;
	class EntityType;
	class GameEntity;
	class LogicalSpace;
	class State;
	class VirtualSpace;

	using namespace std;

	typedef struct t_pos {
		t_pos() : x(0), y(0), z(0) {}
		t_pos( float _x, float _y, float _z ) :
			x( _x ), y( _y ), z( _z ) {}

		float getX() const { return x; }
		float getY() const { return y; }
		float getZ() const { return z; }

		void setX( float _x ) { x = _x; }
		void setY( float _y ) { y = _y; }
		void setZ( float _z ) { z = _z; }

	private:
		float x;
		float y;
		float z;
	} t_pos;

	typedef struct {
		float width;
		float height;
	} t_size;

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

