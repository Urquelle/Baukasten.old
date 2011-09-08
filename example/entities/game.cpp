#include "game.h"
#include "lua/bindings.h"
#include "world_map.h"
#include "forms/worldmap_form.h"

#include <core_services.h>
#include <generic_state.h>
#include <lua/action.h>
#include <irrlicht/irrlicht_graphics.h>
#include <irrlicht/irrlicht_input.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;

enum Mode { MODE_WORLDMAP, MODE_MENU, MODE_BATTLE };

Game::Game( const std::string &id ) :
	GameEntity( id )
{
	addState( "keepRunning", new StateInt( "keepRunning", 1 ) );
	addState( "currentMode", new StateInt( "currentMode", MODE_WORLDMAP ) );

	addAction( new ActionLua( *this, "updateState", "scripts/update_state.lua" ) );
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

void Game::onKeyDown( Key key, Modifier mod )
{
	if ( key == Baukasten::KEY_Q ) {
		getState<StateInt*>( "keepRunning" )->setValue( 0 );
	}
}

void Game::run()
{
	// mainloop
	while ( keepRunning() ) {
		invokeAction( "updateState" );

		runActions();
		mGraphics->getDriver()->beginScene(true, true, video::SColor(0, 0, 0, 0));
		mGraphics->render( getForm() );
		mGraphics->getDriver()->endScene();
		mInput->process();
	}

	std::cout << "... GAME OVER!!! ..." << endl;
}

int Game::init()
{
	initBindings();

	CoreServices *services = new CoreServices();

	services->init();

	mInput = dynamic_cast<IrrlichtInput*>( services->getInputService() );
	mGraphics = dynamic_cast<IrrlichtGraphics*>( services->getVideoService() );

	mGraphics->getDevice()->setWindowCaption( L"Eisenfaust" );

	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init Entities
	mWorldMap = new WorldMap( "worldmap" );

	WorldMapForm *form = new WorldMapForm(
		"form:worldmap",
		mGraphics
	);

	mWorldMap->setForm( form );
	getForm()->addToVSpace( form );

	addChild( mWorldMap );
}

