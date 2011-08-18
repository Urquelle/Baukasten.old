#include "example_game.h"
#include "entities.h"

#include <iostream>

#if defined(USE_OGRE)
#include "frame_listener.h"
#include <OGRE/Ogre.h>

void initSceneOgre( Ogre::Node *root )
{
}
#endif

ExampleGame::ExampleGame() :
    mKeepRunning( true )
#if defined(USE_OGRE)
    , mRoot( 0 )
    , mSceneManager( 0 )
    , mWindow( 0 )
    , mCamera( 0 )
    , mListener( 0 )
#endif
{
    using namespace Baukasten::Core;
    using namespace std;

    Unit *sanchez = new Unit( "sanchez" );
    Unit *gomez = new Unit( "gomez" );
	Unit *ramirez = new Unit( "ramirez" );

	EntityList targets;

	targets.push_back( gomez );
	targets.push_back( ramirez );

    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();
    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();
    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();
    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();
}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::start()
{
    /*
    std::cout << "spiel starten." << std::endl;
    initRenderingSystem();
    initScene( "test" );
    run();
    */
}

void ExampleGame::pause()
{
    std::cout << "spiel pausieren." << std::endl;
}

void ExampleGame::stop()
{
    std::cout << "spiel stoppen." << std::endl;
}

void ExampleGame::run()
{
    while ( mKeepRunning ) {
#if defined(USE_OGRE)
        renderOneFrame();
#else
        break;
#endif
    }
}

void ExampleGame::initRenderingSystem()
{
#if defined(USE_OGRE)
    mRoot = new Ogre::Root();

    if ( !mRoot->restoreConfig() )
        if ( !mRoot->showConfigDialog() )
            mKeepRunning = false;

    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mWindow = mRoot->initialise( "true", "Baukasten Beispielanwendung" );

    mCamera = mSceneManager->createCamera("Camera");
    mCamera->setPosition(Ogre::Vector3(0,0,50));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

    Ogre::Viewport *viewport = mWindow->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));

    mCamera->setAspectRatio(
        Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight())
    );

    mListener = new OgreFrameListener(
        mWindow,
        mCamera,
        viewport
    );

    mRoot->addFrameListener(mListener);
#endif
}

void ExampleGame::initScene( const std::string &scene )
{
#if defined(USE_OGRE)
    initSceneOgre( mSceneManager->getRootSceneNode() );
#endif
}

#if defined(USE_OGRE)
void ExampleGame::renderOneFrame()
{
    Ogre::WindowEventUtilities::messagePump();
    mKeepRunning = mRoot->renderOneFrame();
}
#endif

