#include "ogre/ogre_interface.h"

#include <OGRE/Ogre.h>

#include <iostream>

using namespace Baukasten;

void loadResources()
{
	std::string userHome = getenv( "HOME" );

    Ogre::ConfigFile cf;
    cf.load(userHome + "/.config/baukasten/resources.cfg");

    Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
    Ogre::String sectionName, typeName, dataName;

    while (sectionIter.hasMoreElements()) {
        sectionName = sectionIter.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;

        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            dataName = i->second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				dataName,
				typeName,
				sectionName
			);
        }
    }

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

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

	loadResources();

	mInitialised = true;

	return 1;
}

void OgreInterface::render()
{
	if ( mRoot )
		mRoot->renderOneFrame();
}

void OgreInterface::addForm( Form *form )
{
	std::cout << "in OgreInterface::renderForm" << std::endl;
}

