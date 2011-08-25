#include "example_game.h"
#include "entities.h"
#include "actions/actions.h"
#include "actions/render_scene.h"
#include "forms/world_map_form.h"
#include "world_map.h"

#include <action.h>
#include <generic_state.h>

#include <OGRE/Ogre.h>

#include <iostream>
#include <cstdlib>

using namespace Baukasten;

ExampleGame::ExampleGame( const std::string &id ) :
	GameEntity( id )
{
	addState( "keepRunning", new StateBool( "keepRunning", true ) );

	addAction( "updateState", new UpdateState( *this ) );
	addAction( "renderScene", new RenderScene( *this ) );

	setForm( new Form( "form" ) );
}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::start()
{
	init();
    run();
}

bool ExampleGame::keepRunning() const
{
	return getState<StateBool*>( "keepRunning" )->getValue();
}

void ExampleGame::stop()
{
    std::cout << "spiel stoppen." << std::endl;
}

void ExampleGame::run()
{
    using namespace Baukasten;
    using namespace std;

    Unit *sanchez = new Unit( "sanchez" );
    Unit *gomez = new Unit( "gomez" );
	Unit *ramirez = new Unit( "ramirez" );

	GameEntityList targets;

	targets.push_back( gomez );
	targets.push_back( ramirez );

	while ( keepRunning() ) {

		invokeAction( "updateState", targets );
		invokeAction( "processInput" );
		invokeAction( "renderScene" );

		sanchez->invokeAction( "hit", targets );
		//sanchez->runActions();

		runActions();

		mRoot->renderOneFrame();
	}
}

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
			cout << sectionName << " -> " << typeName << ": " << dataName << endl;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				dataName,
				typeName,
				sectionName
			);
        }
    }

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

int ExampleGame::init()
{
    mRoot = new Ogre::Root("plugins.cfg");

    if (!mRoot->showConfigDialog()) {
        return -1;
    }

    Ogre::RenderWindow *window = mRoot->initialise(true, "Ogre3D Beginners Guide");
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);

	Ogre::Camera *mCamera = mSceneManager->createCamera("Camera");
    mCamera->setPosition(Ogre::Vector3(0,0,50));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    Ogre::Viewport *viewport = window->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));

    mCamera->setAspectRatio(
        Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight())
    );

	getForm()->addObject( "root", mRoot );
	getForm()->addObject( "window", window );
	getForm()->addObject( "sceneManager", mSceneManager );

	loadResources();

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );
	mWorldMap->setForm( new WorldMapForm( "form", mSceneManager ) );

	getForm()->addToLSpace( "objects", mWorldMap );
	getForm()->addToVSpace( "objects", mWorldMap->getForm() );
}

