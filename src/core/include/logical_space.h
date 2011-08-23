#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "global.h"

#include "abstract_space.h"
#include "entity_manager.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT LogicalSpace : public AbstractSpace,
	public EntityManager {
	public:
		LogicalSpace( const std::string& );
		virtual ~LogicalSpace();
	};
}

#endif // LOGICAL_SPACE_H

