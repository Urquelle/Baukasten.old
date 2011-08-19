#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include <list>
#include <memory>
#include <string>
#include <tuple>

namespace Baukasten {
    namespace Core {
        class Action;
        class Entity;
		class GameEntity;
        class State;

        using namespace std;

        typedef tuple<float, float, float> t_pos;

        typedef map<string, Entity*>		EntityMap;
        typedef list<Entity*>				EntityList;

        typedef map<string, GameEntity*>	GameEntityMap;
        typedef list<GameEntity*>			GameEntityList;

        typedef map<string, Action*>		ActionMap;
        typedef list<Action*>				ActionList;

        typedef map<string, State*>			StateMap;
    }
}

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif // GLOBAL_H

