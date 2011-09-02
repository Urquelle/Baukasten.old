#ifndef OGRE_FORM_T3TPCSOI
#define OGRE_FORM_T3TPCSOI

#include "global.h"

#include "form.h"

namespace Baukasten {
	class OgreInterface;

	class OgreForm : public Baukasten::Form {
	public:
		OgreForm( const std::string&, OgreInterface* );
		virtual ~OgreForm();

	private:
		void initScene();

		OgreInterface*	mInterface;
	};
} /* Baukasten */

#endif /* end of include guard: OGRE_FORM_T3TPCSOI */

