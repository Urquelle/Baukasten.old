#include "game.h"

#include "basic_type.h"
#include "entities/unit.h"
#include "forms/form2d.h"
#include "../global.h"
#include "../lua/bindings.h"
#include "world_map.h"

#include <core_services.h>
#include <debug.h>
#include <form.h>
#include <generic_state.h>
#include <igraphics.h>
#include <iinput.h>
#include <lua/action_lua.h>
#include <logical_space.h>

using namespace Baukasten;

Game::Game( const std::string &id ) :
	GameEntity( id ),
	mWorldMap( 0 ), mGraphics( 0 ), mInput( 0 )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );
	addState( "currentMode", new StateInt( "currentMode", Mode::MODE_WORLDMAP ) );

	setForm( new Form( "form" ) );
}

Game::~Game()
{
	mInput->shutDown();
	mGraphics->shutDown();
}

void Game::start()
{
	init();
	run();
}

bool Game::keepRunning()
{
	return getState<StateInt*>( "keepRunning" )->getValue();
}

int Game::currentMode()
{
	return getState<StateInt*>( "currentMode" )->getValue();
}

void Game::onKeyDown( Key key, Modifier mod )
{
	switch ( key ) {
	case Key::KEY_Q:
		switch ( currentMode() ) {
		case Mode::MODE_WORLDMAP:
			getState<StateInt*>( "keepRunning" )->setValue( 0 );
			break;
		}
		break;
	case Key::KEY_RETURN:
		switch ( currentMode() ) {
		case MODE_WORLDMAP:
			mWorldMap->invokeAction( "showMenu" );
			getState<StateInt*>( "currentMode" )->setValue( MODE_MENU );
			break;
		case MODE_MENU:
			mWorldMap->invokeAction( "handleMenuItem" );
			getState<StateInt*>( "currentMode" )->setValue( MODE_WORLDMAP );
			break;
		}
		break;
	}
}

void Game::onKeyUp( Key key, Modifier mod )
{
}

void Game::run()
{
	// mainloop
	while ( keepRunning() ) {
		getForm()->getLSpace()->runActions();
		mInput->process();
		mGraphics->render( getForm() );
	}

	std::cout << "... GAME OVER!!! ..." << endl;
}

int Game::init()
{
	initBindings();

	CoreServices *services = CoreServices::instance();

	services->init();

	mInput = services->getInputService();
	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );
	mInput->onKeyUp().connect( sigc::mem_fun( this, &Game::onKeyUp ) );
	mGraphics = services->getVideoService();
	mGraphics->setWindowCaption( L"Eisenfaust" );

	// init worldmap
	mWorldMap = new WorldMap( "entity:worldmap" );
	getForm()->addToVSpace( mWorldMap->getForm() );
	getForm()->addToLSpace( mWorldMap );

	// init hero's group and some units
	BasicType *type = new BasicType( "basic" );
	GameEntity *group = new GameEntity( "entity:heroGroup" );

	Unit *sanchez = new Unit( "unit:sanchez" );
	Unit *gomez = new Unit( "unit:gomez" );
	Unit *ramirez = new Unit( "unit:ramirez" );

	sanchez->setType( type );
	gomez->setType( type );
	ramirez->setType( type );

	sanchez->setName( "sanchez" );
	gomez->setName( "gomez" );
	ramirez->setName( "ramirez" );

	group->addChild( sanchez );
	group->addChild( gomez );
	group->addChild( ramirez );

	Form2d *form = new Form2d(
		"form:group",
		"media/images/1024x768/group.jpg",
		services->getVideoService()
	);

	form->setPosition( { 515, 338, 0 } );
	form->setSize( { 30, 30 } );
	form->setVisible( true );
	form->addState( new StateString( "state:currentCity", "city:berlin" ) );

	group->setForm( form );
	mWorldMap->getForm()->addToVSpace( form );

	addChild( mWorldMap );
	addChild( group );
}

