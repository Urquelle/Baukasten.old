#ifndef OGRE_INTERFACE_DK716OON
#define OGRE_INTERFACE_DK716OON

#include "igraphics.h"

namespace Baukasten {
	class OgreInterface : public IGraphics {
	public:
		OgreInterface();
		virtual ~OgreInterface();

		void init();
		void renderForm( Form* );
	};
} /* Baukasten */

#endif /* end of include guard: OGRE_INTERFACE_DK716OON */
