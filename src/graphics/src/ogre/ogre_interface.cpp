#include "ogre/ogre_interface.h"

#include <OGRE/Ogre.h>

#include <iostream>

using namespace Baukasten;

OgreInterface::OgreInterface() :
	IGraphics()
{
}

OgreInterface::~OgreInterface()
{
}

int OgreInterface::init()
{
	mRoot = new Ogre::Root("plugins.cfg");

	if ( !mRoot->showConfigDialog() ) {
		return 0;
	}

	mRoot->initialise( true, "" );
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "sceneManager");

	mInitialised = true;

	return 1;
}

void OgreInterface::renderForm( Form *form )
{
	if ( !mInitialised && !init() )
		return;

	std::cout << "in OgreInterface::renderForm" << std::endl;
}

