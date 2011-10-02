#include "game.h"

#include "actions.h"
#include "field_form.h"
#include "block_form.h"
#include "form2d.h"

#include <lua/action_lua.h>
#include <core_services.h>
#include <generic_state.h>
#include <iinput.h>
#include <igraphics.h>
#include <logical_space.h>
#include <virtual_space.h>

using namespace Baukasten;

Game::Game( const string &id ) :
	GameEntity( id )
{
	addAction( new ActionLua( *this, "action:rotate", "scripts/rotate.lua" ) );
	addAction( new ActionLambda( *this, "action:moveLeft", &moveLeft ) );
	addAction( new ActionLambda( *this, "action:moveRight", &moveRight ) );

	addState( new StateBool( "state:keepRunning", true ) );

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

	mInput->onKeyDown().connect( sigc::mem_fun( this, &Game::onKeyDown ) );

	// init main display
	GameEntity *display = new GameEntity( "entity:display ");
	display->setForm(
		new Form2d( "form:display", "media/display.png", mGraphics )
	);

	display->getForm()->setPosition( { 0, 0, 0 } );
	display->getForm()->setSize( { 1024, 768 } );

	addChild( display );
	getForm()->addToVSpace( display->getForm() );
	getForm()->addToLSpace( display );

	// init playfield
	GameEntity *field = new GameEntity( "entity:field" );
	field->addAction( new ActionLambda( *field, "action:recalculate", &recalc, &recalcDone ) );
	field->addState( new StateInt( "state:column", 0 ) );
	field->addState( new StateInt( "state:row", 0 ) );
	field->addState( new StateInt( "state:rows", 18 ) );
	field->setForm( new FieldForm( "form:field", mGraphics ) );
	field->getForm()->addState( new StateInt( "state:currentLine", 0 ) );
	field->getForm()->setPosition( { 240, 20, 0 } );
	field->getForm()->setSize( { 480, 720 } );

	// 13x18
	field->getForm()->addState( new StateIntVector( "state:field", {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}));

	addChild( field );
	getForm()->addToVSpace( field->getForm() );
	getForm()->addToLSpace( field );
	field->invokeAction( "action:recalculate" );

	// init blocks
	GameEntity *blockO = new GameEntity( "block:o" );
	blockO->setForm( new BlockForm( "form:o", mGraphics ) );
	blockO->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockO->getForm()->addState( new StateIntVector( "state:limit1", { 1, 1, 1, 1 } ) );
	blockO->getForm()->addState( new StateIntVector( "state:limit2", { 1, 1, 1, 1 } ) );
	blockO->getForm()->addState( new StateIntVector( "state:limit3", { 1, 1, 1, 1 } ) );
	blockO->getForm()->addState( new StateIntVector( "state:limit4", { 1, 1, 1, 1 } ) );
	blockO->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockO->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));

	GameEntity *blockZ = new GameEntity( "block:z" );
	blockZ->setForm( new BlockForm( "form:z", mGraphics ) );
	blockZ->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockZ->getForm()->addState( new StateIntVector( "state:limit1", { 1, 1, 1, 2 } ) );
	blockZ->getForm()->addState( new StateIntVector( "state:limit2", { 1, 1, 2, 1 } ) );
	blockZ->getForm()->addState( new StateIntVector( "state:limit3", { 1, 1, 1, 2 } ) );
	blockZ->getForm()->addState( new StateIntVector( "state:limit4", { 1, 1, 2, 1 } ) );
	blockZ->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		1, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockZ->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 1, 0, 0
	}));

	GameEntity *blockS = new GameEntity( "block:s" );
	blockS->setForm( new BlockForm( "form:s", mGraphics ) );
	blockS->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockS->getForm()->addState( new StateIntVector( "state:limit1", { 1, 1, 1, 2 } ) );
	blockS->getForm()->addState( new StateIntVector( "state:limit2", { 1, 1, 2, 1 } ) );
	blockS->getForm()->addState( new StateIntVector( "state:limit3", { 1, 1, 1, 2 } ) );
	blockS->getForm()->addState( new StateIntVector( "state:limit4", { 1, 1, 2, 1 } ) );
	blockS->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockS->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0
	}));

	GameEntity *blockT = new GameEntity( "block:t" );
	blockT->setForm( new BlockForm( "form:t", mGraphics ) );
	blockT->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockT->getForm()->addState( new StateIntVector( "state:limit1", { 1, 1, 1, 2 } ) );
	blockT->getForm()->addState( new StateIntVector( "state:limit2", { 1, 1, 2, 1 } ) );
	blockT->getForm()->addState( new StateIntVector( "state:limit3", { 1, 1, 1, 2 } ) );
	blockT->getForm()->addState( new StateIntVector( "state:limit4", { 1, 1, 2, 1 } ) );
	blockT->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockT->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 1, 0,
		0, 0, 1, 0
	}));

	GameEntity *blockL = new GameEntity( "block:l" );
	blockL->setForm( new BlockForm( "form:l", mGraphics ) );
	blockL->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockL->getForm()->addState( new StateIntVector( "state:limit1", { 1, 1, 2, 1 } ) );
	blockL->getForm()->addState( new StateIntVector( "state:limit2", { 1, 1, 1, 2 } ) );
	blockL->getForm()->addState( new StateIntVector( "state:limit3", { 1, 1, 2, 1 } ) );
	blockL->getForm()->addState( new StateIntVector( "state:limit4", { 1, 1, 1, 2 } ) );
	blockL->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 1, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 1, 0
	}));
	blockL->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		1, 0, 0, 0,
		0, 0, 0, 0
	}));

	GameEntity *blockJ = new GameEntity( "block:j" );
	blockJ->setForm( new BlockForm( "form:j", mGraphics ) );
	blockJ->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockJ->getForm()->addState( new StateIntVector( "state:limit1", { 1, 1, 2, 1 } ) );
	blockJ->getForm()->addState( new StateIntVector( "state:limit2", { 1, 1, 1, 2 } ) );
	blockJ->getForm()->addState( new StateIntVector( "state:limit3", { 1, 1, 2, 1 } ) );
	blockJ->getForm()->addState( new StateIntVector( "state:limit4", { 1, 1, 1, 2 } ) );
	blockJ->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 0, 0, 0,
		0, 0, 1, 0,
		0, 0, 1, 0,
		0, 1, 1, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 1, 0,
		0, 0, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockJ->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		1, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0
	}));

	GameEntity *blockI = new GameEntity( "block:i" );
	blockI->setForm( new BlockForm( "form:i", mGraphics ) );
	blockI->getForm()->addState( new StateInt( "state:currentMatrix", 1 ) );
	blockI->getForm()->addState( new StateIntVector( "state:limit1", { 2, 0, 2, 1 } ) );
	blockI->getForm()->addState( new StateIntVector( "state:limit2", { -1, 2, 1, 2 } ) );
	blockI->getForm()->addState( new StateIntVector( "state:limit3", { 2, 0, 2, 1 } ) );
	blockI->getForm()->addState( new StateIntVector( "state:limit4", { -1, 2, 1, 2 } ) );
	blockI->getForm()->addState( new StateIntVector( "state:matrix1", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix2", {
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix3", {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	}));
	blockI->getForm()->addState( new StateIntVector( "state:matrix4", {
		0, 0, 0, 0,
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0
	}));

	GameEntity *blockGroup = new GameEntity( "entity:group" );
	blockGroup->addAction( new ActionLambda( *blockGroup, "action:nextBlock", &nextBlock ) );
	blockGroup->addChild( blockO );
	blockGroup->addChild( blockZ );
	blockGroup->addChild( blockS );
	blockGroup->addChild( blockT );
	blockGroup->addChild( blockL );
	blockGroup->addChild( blockJ );
	blockGroup->addChild( blockI );

	addChild( blockGroup );
	blockGroup->invokeAction( "action:nextBlock" );
	getForm()->addToLSpace( blockGroup );
}

void Game::run()
{
	while ( getState<StateBool*>( "state:keepRunning" )->getValue() ) {
		runActions();
		mInput->process();
		mGraphics->render( getForm() );
	}
}

void Game::onKeyDown( Key key, Modifier mod )
{
	switch ( key ) {
	case Key::KEY_Q:
		getState<StateBool*>( "state:keepRunning" )->setValue( false );
		break;
	case Key::KEY_ARROW_UP:
		invokeAction( "action:rotate" );
		break;
	case Key::KEY_ARROW_DOWN:
		break;
	case Key::KEY_ARROW_RIGHT:
		invokeAction( "action:moveRight" );
		break;
	case Key::KEY_ARROW_LEFT:
		invokeAction( "action:moveLeft" );
		break;
	}
}

