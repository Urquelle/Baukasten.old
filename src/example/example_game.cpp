#include "example_game.h"
#include "actions.h"

#include <generic_state.h>

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

    Entity *u = new Entity( "hans" );

    GenericState<string> *sName = new GenericState<string>( *u, "name" );
    GenericState<int> *sLevel = new GenericState<int>( *u, "level" );
    sLevel->setValue( 0 );
    GenericState<int> *sExp = new GenericState<int>( *u, "experience" );

    ActionLevelUp *aLvlUp = new ActionLevelUp( *u );
    ActionAddExperience *aAddExp = new ActionAddExperience( *u );
    Hit *aHit = new Hit( *u );

    u->addState( *sName );
    u->addState( *sLevel );
    u->addState( *sExp );

    u->addAction( *aLvlUp );
    u->addAction( *aAddExp );
    u->addAction( *aHit );

    Entity *u2 = new Entity( "gomez" );

    GenericState<int> *sHP = new GenericState<int>( *u2, "hp" );
    sHP->setValue( 10 );

    u2->addState( *sHP );

	Entity *u3 = new Entity( "ramirez" );

	GenericState<int> *sHP2 = new GenericState<int>( *u3, "hp" );
	sHP2->setValue( 15 );

	u3->addState( *sHP2 );

    std::cout << u->getId() << " level: " << sLevel->getValue() << std::endl;
    std::cout << u2->getId() << " hp: " << ( static_cast<GenericState<int>*>( u2->getState( "hp" ) ) )->getValue() << std::endl;
    std::cout << u3->getId() << " hp: " << sHP2->getValue() << std::endl;

	EntityList targets;

	targets.push_back( u2 );
	targets.push_back( u3 );

    u->invokeAction( aAddExp->getId() );
    u->invokeAction( aHit->getId(), targets );
    u->runActions();

    std::cout << u2->getId() << " hp: " << sHP->getValue() << std::endl;
    std::cout << u3->getId() << " hp: " << sHP2->getValue() << std::endl;
    std::cout << u->getId() << " level: " << sLevel->getValue() << std::endl;
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

