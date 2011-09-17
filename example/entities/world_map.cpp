#include "world_map.h"

#include "core_services.h"
#include "forms/form2d.h"
#include "forms/menu_form.h"

#include <action_lambda.h>
#include <lua/action_lua.h>
#include <generic_state.h>

using namespace Baukasten;

GameEntity* createPointer()
{
	t_pos berlin = { 467, 338, 100 };
	t_pos mannheim = { 420, 410, 100 };

	CoreServices *services = CoreServices::instance();

	GameEntity *pointer = new GameEntity( "entity:pointer" );
	pointer->addState( new StateString( "state:currentCity", "berlin" ) );

	Form2d *form = new Form2d(
		"form:pointer",
		"media/images/1024x768/pointer.png",
		services->getVideoService()
	);

	form->setSize( { 50, 39 } );
	form->setPosition( berlin );

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

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addAction( new ActionLua( *this, "moveRightOnMap", "scripts/move_right_on_map.lua" ) );
	addAction( new ActionLua( *this, "moveLeftOnMap", "scripts/move_left_on_map.lua" ) );
	addAction( new ActionLambda( *this, "showMenu", &showMenuFunction ) );
	addAction( new ActionLambda( *this, "hideMenu", &hideFunction ) );

	CoreServices *services = CoreServices::instance();

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
}

WorldMap::~WorldMap()
{
}

