#include <form.h>

namespace Ogre{
	class Root;
}

class OgreForm : public Baukasten::Form {
public:
	OgreForm( const std::string&, Ogre::Root* );
	virtual ~OgreForm();

	Ogre::Root* getRoot() const;

private:
	Ogre::Root* mRoot;
};
