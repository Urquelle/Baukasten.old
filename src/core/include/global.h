#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>
#include <memory>
#include <string>
#include <tuple>

namespace Baukasten {
    namespace Core {
        class Action;
        class State;

        using namespace std;

        typedef tuple<float, float, float> t_pos;
        typedef map<string, Action*> ActionMap;
        typedef map<string, State*> StateMap;
    }
}

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif // GLOBAL_H

