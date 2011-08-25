#include "world_map_form.h"

#include <OGRE/Ogre.h>

WorldMapForm::WorldMapForm( const std::string &id, Ogre::SceneManager *sceneManager ) :
	OgreForm( id, sceneManager )
{
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

void WorldMapForm::renderScene()
{
}

