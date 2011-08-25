#include "world_map_form.h"

#include <OGRE/Ogre.h>

WorldMapForm::WorldMapForm( const std::string &id, Ogre::Root *root ) :
	OgreForm( id, root )
{
	/**
	 * initialise the scene.
	 *
	 * position the camera and add a viewport. create the entities
	 * that belong to the worldmap itself.
	 */

	Ogre::SceneManager *sceneManager = root->getSceneManager( "sceneManager" );

	// create camera
	Ogre::Camera *mCamera = sceneManager->createCamera("Camera");

    mCamera->setPosition( Ogre::Vector3( 0, 400, 500) );
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);

	// add viewport
	Ogre::RenderWindow *window = root->getAutoCreatedWindow();
    Ogre::Viewport *viewport = window->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));

    mCamera->setAspectRatio(
        Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight())
    );

	// create plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
    Ogre::MeshManager::getSingleton().createPlane(
        "plane",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane,
        1500,1500,200,200,true,1,5,5,Ogre::Vector3::UNIT_Z
    );

    mGround = sceneManager->createEntity( "LightPlaneEntity", "plane" );

    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(mGround);
    mGround->setMaterialName("Examples/BeachStones");

    Ogre::Light *light = sceneManager->createLight("light1");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(1,-1,0));

    sceneManager->setShadowTechnique(
        Ogre::SHADOWTYPE_STENCIL_ADDITIVE
    );
}

WorldMapForm::~WorldMapForm()
{
}

void WorldMapForm::render()
{
}

