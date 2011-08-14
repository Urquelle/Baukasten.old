#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "abstract_space.h"

namespace Eisenfaust
{
    namespace Core
    {
        class LogicalSpace : public AbstractSpace
        {
        public:
            LogicalSpace();
            virtual ~LogicalSpace();
        };
    }
}

#endif // LOGICAL_SPACE_H

