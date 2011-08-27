#include <form.h>

namespace Ogre{
	class Root;
}

class OgreForm : public Baukasten::Form {
public:
	OgreForm( const std::string& );
	virtual ~OgreForm();
};
