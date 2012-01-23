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

	using namespace std;

	template<class T> class v2 {
	public:
		v2() {}
		v2( T x, T y ) :
			mX( x ), mY( y ) {}

		T getX() const { return mX; }
		T getY() const { return mY; }

	private:
		T mX, mY;
	};

	template<class T> class v3 {
	public:
		v3() {}
		v3( T x, T y, T z ) :
			mX( x ), mY( y ), mZ( z ) {}

		T getX() const { return mX; }
		T getY() const { return mY; }
		T getZ() const { return mZ; }

		void setX( T x ) { mX = x; }
		void setY( T y ) { mY = y; }
		void setZ( T z ) { mZ = z; }

	private:
		T mX, mY, mZ;
	};

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

