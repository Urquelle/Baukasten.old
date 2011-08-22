#ifndef FORM_H
#define FORM_H

#include "abstract_space.h"
#include "drawable.h"
#include "global.h"

#include <string>

namespace Baukasten {
	class BAUKASTEN_EXPORT Form : public Drawable {
	public:
		Form( const std::string& );
		virtual ~Form();

		void addSpace( const std::string&, AbstractSpace* );

	protected:
		std::string mMeshName;
		EntityMap   mSpaceMap;
	};
}

#endif // FORM_H

