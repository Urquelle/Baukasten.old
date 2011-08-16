#include "frame_listener.h"

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>

OgreFrameListener::OgreFrameListener(
        Ogre::RenderWindow *win,
        Ogre::Camera *cam,
        Ogre::Viewport *viewport ) :
    mCamera( cam ),
    mViewport( viewport )
{
    OIS::ParamList params;

    /*
     * die variable _muss_ vom typ size_t sein und nicht
     * unsigned int! mit unsigned int gibt es ein SIGSEV.
     */
    size_t windowHandle = 0;
    std::ostringstream windowHandleString;

    win->getCustomAttribute("WINDOW", &windowHandle);
    windowHandleString << windowHandle;

    params.insert(
        std::make_pair("WINDOW", windowHandleString.str())
    );

    mInputManager = OIS::InputManager::createInputSystem(params);
    mKeyboard = static_cast<OIS::Keyboard*>(
        mInputManager->createInputObject(OIS::OISKeyboard, false)
    );

    mMouse = static_cast<OIS::Mouse*>(
        mInputManager->createInputObject( OIS::OISMouse, false )
    );
}

OgreFrameListener::~OgreFrameListener()
{
    mInputManager->destroyInputObject(mKeyboard);
    mInputManager->destroyInputObject(mMouse);
    OIS::InputManager::destroyInputSystem(mInputManager);
}

bool OgreFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
    mKeyboard->capture();
    mMouse->capture();

    if ( mKeyboard->isKeyDown( OIS::KC_ESCAPE ) )
        return false;
    return true;
}

bool OgreFrameListener::frameEnded(const Ogre::FrameEvent &evt)
{
    return true;
}

bool OgreFrameListener::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    return true;
}
