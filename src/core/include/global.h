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
        class State;
        class Entity;

        using namespace std;

        typedef tuple<float, float, float> t_pos;

        typedef map<string, Entity*>    EntityMap;
        typedef list<Entity*>           EntityList;

        typedef map<string, Action*>    ActionMap;
        typedef list<Action*>           ActionList;

        typedef map<string, State*>     StateMap;
    }
}

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif // GLOBAL_H

