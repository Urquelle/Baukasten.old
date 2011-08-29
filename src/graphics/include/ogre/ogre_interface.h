#ifndef OGRE_INTERFACE_DK716OON
#define OGRE_INTERFACE_DK716OON

#include "igraphics.h"

#include <map>
#include <string>

namespace Ogre {
	class Node;
	class Root;
	class SceneManager;
}

namespace Baukasten {
	using namespace std;

	typedef map<const string, Ogre::Node*> NodeMap;

	class OgreInterface : public IGraphics {
	public:
		OgreInterface();
		virtual ~OgreInterface();

		int init();
		void render();
		void addForm( Form* );

	private:
		Ogre::Root*			mRoot;
		Ogre::SceneManager*	mSceneManager;
		NodeMap				mForms;
	};
} /* Baukasten */

#endif /* end of include guard: OGRE_INTERFACE_DK716OON */
