/*!
 * \file model/include/global.h
 *
 * \brief global include file for Model module.
 *
 * this file contains all the basic declarations that
 * are used across the model module.
 */

/*! \defgroup action Action */
/*! \defgroup entity Entity */
/*! \defgroup manager Manager */
/*! \defgroup model Model */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "core/Global"

namespace Baukasten {
	using namespace std;

	class Action;
	class Drawable;
	class Entity;
	class EntityType;
	class GameEntity;
	class LogicalSpace;
	class State;
	class VirtualSpace;

	/*!
	 * the map consists of a key string, being the id of the
	 * Entity and the Entity object itself, which is stored
	 * in a shared_ptr.
	 */
	typedef map<string, shared_ptr<Entity> > EntityMap;
	typedef vector<shared_ptr<Entity> >		EntityList;

	typedef map<string, shared_ptr<EntityType> > EntityTypeMap;
	typedef vector<shared_ptr<EntityType> >	EntityTypeList;

	typedef map<string, shared_ptr<GameEntity> > GameEntityMap;
	typedef vector<shared_ptr<GameEntity> >	GameEntityList;

	typedef map<string, shared_ptr<Action> >	ActionMap;
	typedef vector<shared_ptr<Action> >		ActionList;

	typedef map<string, LogicalSpace*>		LSpaces;
	typedef map<string, shared_ptr<VirtualSpace> > VSpaces;

	typedef map<string, shared_ptr<State> >	StateMap;
	typedef vector<shared_ptr<State> >			StateList;
} /* Baukasten */


#endif // GLOBAL_H

