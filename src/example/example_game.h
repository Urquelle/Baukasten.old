#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <string>

#if defined(USE_OGRE)
    namespace Ogre {
        class Root;
        class SceneManager;
        class RenderWindow;
        class Camera;
    }

    class OgreFrameListener;
#endif

class ExampleGame
{
public:
    ExampleGame();
    virtual ~ExampleGame();

    void start();
    void pause();
    void stop();

protected:
    void run();
    void processUserInput();
    void renderScene();

    void initRenderingSystem();
    void initScene( const std::string& );

#if defined(USE_OGRE)
    void renderOneFrame();
#endif

    bool mKeepRunning;

#if defined(USE_OGRE)
    Ogre::Root*             mRoot;
    Ogre::SceneManager*     mSceneManager;
    Ogre::RenderWindow*     mWindow;
    Ogre::Camera*           mCamera;
    OgreFrameListener*      mListener;
#endif
};

#endif /* end of include guard: GAME_QESA072Y */

