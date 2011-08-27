#include "actions/render_scene.h"
#include "basic_type.h"
#include "example_game.h"
#include "forms/world_map_form.h"
#include "unit.h"
#include "world_map.h"

#include <action.h>
#include <generic_state.h>
#include <lua/action.h>

#include <OGRE/Ogre.h>

#include <iostream>
#include <cstdlib>

using namespace Baukasten;

ExampleGame::ExampleGame( const std::string &id ) :
	GameEntity( id )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );

	addAction( new ActionLua( *this, "updateState", "scripts/update_state.lua" ) );
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
	return getState<StateInt*>( "keepRunning" )->getValue();
}

void ExampleGame::run()
{
    using namespace Baukasten;
    using namespace std;

	invokeAction( "renderScene" );

	// mainloop
	while ( keepRunning() ) {

		invokeAction( "updateState" );
		invokeAction( "processInput" );

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

	mRoot->initialise( true, getId() );
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "sceneManager");

	loadResources();

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );
	mWorldMap->setForm( new WorldMapForm( "form", mRoot ) );

	addChild( mWorldMap );

	BasicType *type = new BasicType( "basic" );

    Unit *sanchez = new Unit( "sanchez" );
    Unit *gomez = new Unit( "gomez" );
	Unit *ramirez = new Unit( "ramirez" );

	sanchez->setType( type );
	gomez->setType( type );
	ramirez->setType( type );

	sanchez->setName( sanchez->getId() );
	gomez->setName( gomez->getId() );
	ramirez->setName( ramirez->getId() );

	addChild( sanchez );
	addChild( gomez );
	addChild( ramirez );

	GameEntityList targets;

	targets.push_back( gomez );
	targets.push_back( ramirez );

	sanchez->invokeAction( "hit", targets );
}

