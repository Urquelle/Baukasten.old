#ifndef LOGICAL_SPACE_H
#define LOGICAL_SPACE_H

#include "model/Global"

namespace Baukasten {
	class BAUKASTEN_EXPORT LogicalSpace {
	public:
		LogicalSpace();
		virtual ~LogicalSpace();

		void runActions();

		GameEntity* entity( const string& ) const;
		void addEntity( const string&, GameEntity* );
		void addEntity( GameEntity* );
		list<GameEntity*> entities() const;
		bool hasEntity( const string& ) const;
		void removeEntity( const string& );

	private:
		list<GameEntity*>			m_list;
		map<string, GameEntity*>	m_map;
	};
}

#endif // LOGICAL_SPACE_H

