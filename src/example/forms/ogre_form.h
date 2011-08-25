#include <form.h>

namespace Ogre{
	class SceneManager;
}

class OgreForm : public Baukasten::Form {
public:
	OgreForm( const std::string&, Ogre::SceneManager* );
	virtual ~OgreForm();

	Ogre::SceneManager* getSceneManager() const;

	virtual void renderScene() = 0;

private:
	Ogre::SceneManager*	mSceneManager;
};
