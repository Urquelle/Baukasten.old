#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "global.h"
#include "abstract_space.h"

namespace Baukasten {
    namespace Core {
        class BAUKASTEN_EXPORT LogicalSpace : public AbstractSpace {
        public:
            LogicalSpace();
            virtual ~LogicalSpace();
        };
    }
}

#endif // LOGICAL_SPACE_H

