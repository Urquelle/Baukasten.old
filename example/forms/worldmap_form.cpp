#include "worldmap_form.h"

#include <ogre/ogre_interface.h>

#include <OGRE/Ogre.h>

#include <iostream>

using namespace Baukasten;
using namespace Ogre;

WorldMapForm::WorldMapForm( const std::string &id, OgreInterface *interface ) :
	OgreForm( id, interface )
{
	SceneManager *manager = getInterface()->getSceneManager();

	MaterialPtr material = MaterialManager::getSingleton().create("Background", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("worldmap.jpg");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	Rectangle2D* rect = new Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("Background");
	rect->setRenderQueueGroup(RENDER_QUEUE_BACKGROUND);
	rect->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));

	// Attach background to the scene
	SceneNode* node = manager->getRootSceneNode()->createChildSceneNode("Background");
	node->attachObject(rect);

	Ogre::Entity* groupSphere = manager->createEntity("GroupPosition","sphere.mesh");
	SceneNode* nodeGroup = node->createChildSceneNode("node");
	nodeGroup->setScale(0.005f,0.005f,0.005f);
	nodeGroup->setPosition(0,0,0);
	nodeGroup->attachObject(groupSphere);
}

WorldMapForm::~WorldMapForm()
{
}

