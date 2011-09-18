#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "global.h"

#include "entity_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT LogicalSpace : public EntityManager {
	public:
		LogicalSpace();
		virtual ~LogicalSpace();

		void runActions();
	};
}

#endif // LOGICAL_SPACE_H

