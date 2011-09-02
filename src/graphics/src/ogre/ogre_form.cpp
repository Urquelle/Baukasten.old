#include "ogre/ogre_form.h"

#include "ogre/ogre_interface.h"

#include <OGRE/Ogre.h>

using namespace Baukasten;

OgreForm::OgreForm( const std::string &id, OgreInterface *interface ) :
	Form( id ),
	mInterface( interface )
{
	initScene();
}

OgreForm::~OgreForm()
{
}

void OgreForm::initScene()
{
}

