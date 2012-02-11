#ifndef VIRTUAL_SPACE_H
#define VIRTUAL_SPACE_H

#include "global.h"

namespace Baukasten {
	class Form;

	class BAUKASTEN_EXPORT VirtualSpace {
	public:
		VirtualSpace();
		virtual ~VirtualSpace();

		Form* entity( const std::string& ) const;
		void addEntity( const string&, Form* );
		void addEntity( Form* );
		list<Form*> entities() const;
		bool hasEntity( const string& ) const;
		void removeEntity( const string& );

	private:
		list<Form*>			mList;
		map<string, Form*>	mMap;
	};
}

#endif // VIRTUAL_SPACE_H

