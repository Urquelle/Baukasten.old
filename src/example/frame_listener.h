#ifndef FRAME_LISTENER_TG6R2XAP
#define FRAME_LISTENER_TG6R2XAP

#include <OGRE/OgreFrameListener.h>

namespace OIS {
    class InputManager;
    class Keyboard;
    class Mouse;
} /* OIS */

namespace Ogre {
    class Camera;
    class SceneNode;
    class AnimationState;
} /* Ogre */

class OgreFrameListener : public Ogre::FrameListener
{
public:
    OgreFrameListener(
        Ogre::RenderWindow*,
        Ogre::Camera*,
        Ogre::Viewport*
    );

    virtual ~OgreFrameListener();

    bool frameStarted(const Ogre::FrameEvent& );
    bool frameEnded(const Ogre::FrameEvent& );
    bool frameRenderingQueued(const Ogre::FrameEvent& );

private:
    OIS::InputManager*      mInputManager;
    OIS::Keyboard*          mKeyboard;
    OIS::Mouse*             mMouse;
    Ogre::Camera*           mCamera;
    float                   mMovementSpeed;

    Ogre::Viewport*         mViewport;

    bool                    mComp1;
    bool                    mDown1;

    bool                    mComp2;
    bool                    mDown2;

    bool                    mComp3;
    bool                    mDown3;

    float                   mWalkingSpeed;
    Ogre::SceneNode*        mNode;

    Ogre::AnimationState*   mAniState;
    Ogre::AnimationState*   mAniStateTop;
};

#endif /* end of include guard: MY_FRAME_LISTENER_TG6R2XAP */
