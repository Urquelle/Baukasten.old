#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "global.h"

namespace Baukasten {
	class BAUKASTEN_EXPORT LogicalSpace {
	public:
		LogicalSpace();
		virtual ~LogicalSpace();

		void runActions();

		GameEntity* getEntity( const string& ) const;
		void addEntity( GameEntity* );
		list<GameEntity*> getEntities() const;
		bool hasEntity( const string& ) const;
		void removeEntity( const string& );

	private:
		list<GameEntity*>			mList;
		map<string, GameEntity*>	mMap;
	};
}

#endif // LOGICAL_SPACE_H

