#ifndef GLOBAL_H
#define GLOBAL_H

#include <tuple>

namespace Baukasten
{
    namespace Core
    {
        typedef std::tuple<float, float, float> t_pos;
    }
}

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif // GLOBAL_H

