#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "global.h"

#include "gameentity_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT LogicalSpace : public GameEntityManager {
	public:
		LogicalSpace();
		virtual ~LogicalSpace();

		void runActions();
	};
}

#endif // LOGICAL_SPACE_H

