#include "world_map.h"

#include "city.h"
#include "forms/form2d.h"
#include "forms/menu_form.h"
#include "../global.h"

#include <action_lambda.h>
#include <core_services.h>
#include <iinput.h>
#include <lua/action_lua.h>
#include <generic_state.h>
#include <virtual_space.h>

using namespace Baukasten;

const t_pos posLondon = { 250, 310, 0 };
const t_pos posParis = { 275, 405, 0 };
const t_pos posBerlin = { 515, 345, 0 };
const t_pos posVienna = { 560, 470, 0 };
const t_pos posConst = { 840, 655, 0 };

GameEntity* createPointer()
{
	CoreServices *services = CoreServices::instance();

	GameEntity *pointer = new GameEntity( "entity:pointer" );
	pointer->addState( new StateString( "state:currentCity", "city:berlin" ) );

	Form2d *form = new Form2d(
		"form:pointer",
		"media/images/1024x768/pointer.png",
		services->getVideoService()
	);

	form->setSize( { 50, 39 } );
	pointer->setForm( form );

	return pointer;
}

GameEntity* createMenu()
{
	CoreServices *services = CoreServices::instance();
	GameEntity *menu = new GameEntity( "entity:menu" );

	MenuForm *form = new MenuForm( "form:menu", services->getVideoService() );
	form->setSize( { 100, 40 } );
	form->setPosition( { 0, 0, 0 } );

	menu->setForm( form );

	return menu;
}

DoActionFunction showMenuFunction( []( Action *action, GameEntity *entity )
{
	GameEntity *pointer = action->getSource()->getChild( "entity:pointer" );
	GameEntity *menu = action->getSource()->getChild( "entity:menu" );

	t_pos pos = pointer->getForm()->getPosition();
	t_size size = pointer->getForm()->getSize();

	menu->getForm()->setPosition(
		{ pos.getX() + size.width, pos.getY(), 0 }
	);

	menu->getForm()->setVisible( true );
});

DoActionFunction hideFunction( []( Action *action, GameEntity *entity )
{
	GameEntity *menu = action->getSource()->getChild( "entity:menu" );
	menu->getForm()->setVisible( false );
});

DoActionFunction handleMenuItemFunction( []( Action *action, GameEntity *entity )
{
	enum MenuAction { MOVE, ABORT, QUIT };

	GameEntity *pointer = action->getSource()->getChild( "entity:pointer" );
	GameEntity *menu = action->getSource()->getChild( "entity:menu" );
	GameEntity *game = action->getSource()->getParent();
	MenuForm *form = static_cast<MenuForm*>( menu->getForm() );

	Form *group = action->getSource()->getForm()->getVSpace()->getEntity( "form:group" );

	GameEntity *city = action->getSource()->getChild(
		pointer->getState<StateString*>( "state:currentCity" )->getValue()
	);
	StateString *cityName = city->getState<StateString*>( "state:name" );
	StateInt *timesVisited = city->getState<StateInt*>( "state:visited" );

	t_pos pos = pointer->getForm()->getPosition();
	t_size size = pointer->getForm()->getSize();

	switch ( form->getCurrentIndex() ) {
	case MOVE:
		if ( timesVisited->getValue() == 0 ) {
			game->getState<StateInt*>( "currentMode" )->setValue( Mode::MODE_RUNSCENE );
			city->invokeAction( "runScene" );
			group->setPosition( { pos.getX() + size.width, pos.getY(), 0 } );
		} else {
			BK_DEBUG( "i've seen you here before in " << ". " << timesVisited->getValue() << " times." );
		}
		timesVisited->setValue( timesVisited->getValue() + 1 );
		break;
	case ABORT:
		action->getSource()->invokeAction( "hideMenu" );
		break;
	case QUIT:
		game->getState<StateInt*>( "keepRunning" )->setValue( 0 );
		break;
	}

	form->setVisible( false );
});

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id ),
	mMoveLeft( false ),
	mMoveRight( false ),
	mMoveUp( false ),
	mMoveDown( false )
{
	addAction( new ActionLua( *this, "moveUpOnMap", "scripts/move_up_on_map.lua" ) );
	addAction( new ActionLua( *this, "moveRightOnMap", "scripts/move_right_on_map.lua" ) );
	addAction( new ActionLua( *this, "moveDownOnMap", "scripts/move_down_on_map.lua" ) );
	addAction( new ActionLua( *this, "moveLeftOnMap", "scripts/move_left_on_map.lua" ) );

	addAction( new ActionLambda( *this, "showMenu", &showMenuFunction ) );
	addAction( new ActionLambda( *this, "hideMenu", &hideFunction ) );
	addAction( new ActionLambda( *this, "handleMenuItem", &handleMenuItemFunction ) );

	CoreServices *services = CoreServices::instance();

	services->getInputService()->onKeyDown().connect(
		sigc::mem_fun( this, &WorldMap::onKeyDown )
	);
	services->getInputService()->onKeyUp().connect(
		sigc::mem_fun( this, &WorldMap::onKeyUp )
	);

	Form2d *wmForm = new Form2d(
		"form:worldmap",
		"media/images/1024x768/worldmap.jpg",
		services->getVideoService()
	);

	wmForm->setPosition( { 0, 0, 0 } );
	wmForm->setSize( { 1024, 768 } );

	setForm( wmForm );

	GameEntity *pointer = createPointer();
	wmForm->addToVSpace( pointer->getForm() );
	addChild( pointer );

	GameEntity *menu = createMenu();
	wmForm->addToVSpace( menu->getForm() );
	addChild( menu );

	City *london = new City( "city:london", "media/maps/0" );
	City *paris = new City( "city:paris", "media/maps/1" );
	City *berlin = new City( "city:berlin", "media/maps/2" );
	City *vienna = new City( "city:vienna", "media/maps/3" );
	City *constantinopel = new City( "city:constantinopel", "media/maps/4" );

	london->getState<StateString*>( "state:name" )->setValue( "London" );
	london->getState<StateString*>( "state:cityDown" )->setValue( paris->getId() );

	paris->getState<StateString*>( "state:name" )->setValue( "Paris" );
	paris->getState<StateString*>( "state:cityUp" )->setValue( london->getId() );
	paris->getState<StateString*>( "state:cityRight" )->setValue( berlin->getId() );

	berlin->getState<StateString*>( "state:name" )->setValue( "Berlin" );
	berlin->getState<StateString*>( "state:cityLeft" )->setValue( paris->getId() );
	berlin->getState<StateString*>( "state:cityDown" )->setValue( vienna->getId() );

	vienna->getState<StateString*>( "state:name" )->setValue( "Vienna" );
	vienna->getState<StateString*>( "state:cityUp" )->setValue( berlin->getId() );
	vienna->getState<StateString*>( "state:cityDown" )->setValue( constantinopel->getId() );

	constantinopel->getState<StateString*>( "state:name" )->setValue( "Constantinopel" );
	constantinopel->getState<StateString*>( "state:cityUp" )->setValue( vienna->getId() );

	london->getForm()->setPosition( posLondon );
	paris->getForm()->setPosition( posParis );
	berlin->getForm()->setPosition( posBerlin );
	vienna->getForm()->setPosition( posVienna );
	constantinopel->getForm()->setPosition( posConst );

	addChild( london );
	addChild( paris );
	addChild( berlin );
	addChild( vienna );
	addChild( constantinopel );

	getForm()->addToVSpace( "form:berlin", berlin->getForm() );
	getForm()->addToLSpace( berlin );
	getForm()->addToVSpace( "form:vienna", vienna->getForm() );
	getForm()->addToLSpace( vienna );

	pointer->getForm()->setPosition( berlin->getForm()->getPosition() );
}

WorldMap::~WorldMap()
{
}

void WorldMap::onKeyDown( Key key, Modifier mod )
{
	StateInt *mode = getParent()->getState<StateInt*>( "currentMode" );

	switch ( mode->getValue() ) {
	case Mode::MODE_MENU:
		switch ( key ) {
		case Key::KEY_Q:
			invokeAction( "hideMenu" );
			mode->setValue( Mode::MODE_WORLDMAP );
			break;
		}
		break;
	case Mode::MODE_WORLDMAP:
		switch ( key ) {
		case Key::KEY_ARROW_LEFT:
			if ( !mMoveLeft ) {
				invokeAction( "moveLeftOnMap" );
				mMoveLeft = true;
			}
			break;
		case Key::KEY_ARROW_RIGHT:
			if ( !mMoveRight ) {
				invokeAction( "moveRightOnMap" );
				mMoveRight = true;
			}
			break;
		case Key::KEY_ARROW_UP:
			if ( !mMoveUp ) {
				invokeAction( "moveUpOnMap" );
				mMoveUp = true;
			}
			break;
		case Key::KEY_ARROW_DOWN:
			if ( !mMoveDown ) {
				invokeAction( "moveDownOnMap" );
				mMoveDown = true;
			}
			break;
		}
		break;
	}
}

void WorldMap::onKeyUp( Key key, Modifier mod )
{
	StateInt *mode = getParent()->getState<StateInt*>( "currentMode" );

	switch ( mode->getValue() ) {
	case Mode::MODE_MENU:
		switch ( key ) {
		case Key::KEY_Q:
			break;
		}
		break;
	case Mode::MODE_WORLDMAP:
		switch ( key ) {
		case Key::KEY_ARROW_LEFT:
			mMoveLeft = false;
			break;
		case Key::KEY_ARROW_RIGHT:
			mMoveRight = false;
			break;
		case Key::KEY_ARROW_UP:
			mMoveUp = false;
			break;
		case Key::KEY_ARROW_DOWN:
			mMoveDown = false;
			break;
		}
		break;
	}
}

