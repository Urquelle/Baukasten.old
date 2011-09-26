#include "game.h"

#include "form2d.h"

#include <core_services.h>
#include <iinput.h>
#include <igraphics.h>
#include <logical_space.h>
#include <virtual_space.h>

using namespace Baukasten;

Game::Game( const string &id ) :
	GameEntity( id )
{
	setForm( new Form( "form:main" ) );
}

Game::~Game()
{
}

void Game::start()
{
	init();
	run();
}

void Game::init()
{
	CoreServices* service = CoreServices::instance();

	service->init();
	mInput = service->getInputService();
	mGraphics = service->getVideoService();

	// init entities
	GameEntity *display = new GameEntity( "entity:display ");
	display->setForm(
		new Form2d( "form:display", "media/display.png", mGraphics )
	);

	display->getForm()->setPosition( { 0, 0, 0 } );
	display->getForm()->setSize( { 1024, 768 } );

	addChild( display );
	getForm()->addToVSpace( display->getForm() );
	getForm()->addToLSpace( display );
}

void Game::run()
{
	while ( true ) {
		getForm()->getLSpace()->runActions();
		mInput->process();
		mGraphics->render( getForm() );
	}
}

