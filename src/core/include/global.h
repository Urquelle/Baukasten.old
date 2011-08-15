#ifndef GLOBAL_H
#define GLOBAL_H

#include <tuple>

namespace Eisenfaust
{
    namespace Core
    {
        typedef std::tuple<float, float, float> t_pos;
    }
}

#if defined(EXPORT_LIB)
#   define EF_EXPORT __attribute__((visibility("default")))
#else
#   define EF_EXPORT
#endif

#endif // GLOBAL_H

