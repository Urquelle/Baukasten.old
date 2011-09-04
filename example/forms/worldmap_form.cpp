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

	// Example of background scrolling
	//material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setScrollAnimation(-0.25, 0.0);
}

WorldMapForm::~WorldMapForm()
{
}

