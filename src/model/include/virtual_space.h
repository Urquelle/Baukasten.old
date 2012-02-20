#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "model/Global"

namespace Baukasten {
	class Form;

	class BAUKASTEN_EXPORT VirtualSpace {
	public:
		VirtualSpace();
		virtual ~VirtualSpace();

		Form* entity( const string& ) const;
		void addEntity( const string&, Form* );
		void addEntity( Form* );
		list<Form*> entities() const;
		bool hasEntity( const string& ) const;
		void removeEntity( const string& );

	private:
		list<Form*>			m_list;
		map<string, Form*>	m_map;
	};
}

#endif // VIRTUAL_SPACE_H

