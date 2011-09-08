#include "ogre/ogre_graphics.h"

#include "ogre/ogre_form.h"

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

OgreGraphics::OgreGraphics() :
	IGraphics()
{
}

OgreGraphics::~OgreGraphics()
{
}

int OgreGraphics::init( CoreServices *coreServices )
{
	mRoot = new Ogre::Root("plugins.cfg");

	if ( !mRoot->showConfigDialog() ) {
		return 0;
	}

	mRoot->initialise( false );
	Ogre::NameValuePairList misc;
	misc["currentGLContext"] = "True";
	Ogre::RenderWindow *renderWindow =
		mRoot->createRenderWindow("MainRenderWindow", 1024, 768, false, &misc);
	renderWindow->setVisible(true);

	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "sceneManager");

    mCamera = mSceneManager->createCamera("Camera");
    mCamera->setPosition(Ogre::Vector3(0,0,50));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    Ogre::Viewport *viewport = renderWindow->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));

    mCamera->setAspectRatio(
        Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight())
    );

	loadResources();

	mInitialised = true;

	return 1;
}

void OgreGraphics::render()
{
	if ( mRoot )
		mRoot->renderOneFrame();
}

Ogre::Root* OgreGraphics::getRoot() const
{
	return mRoot;
}

Ogre::SceneManager* OgreGraphics::getSceneManager() const
{
	return mSceneManager;
}

void OgreGraphics::shutDown()
{
	// do some cleanup
}

