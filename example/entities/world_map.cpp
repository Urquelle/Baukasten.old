#include "world_map.h"

#include "core_services.h"
#include "forms/form2d.h"

#include <action_lambda.h>
#include <lua/action_lua.h>
#include <form.h>
#include <generic_state.h>
#include <igraphics.h>
#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;
using namespace gui;

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

IGUIListBox *listBox = 0;
DoActionFunction showMenuFunction( []( Action *action, GameEntity *entity ) {
		GameEntity *pointer = action->getSource()->getChild( "entity:pointer" );

		CoreServices *services = CoreServices::instance();
		IrrlichtGraphics *graphics =
			dynamic_cast<IrrlichtGraphics*>( services->getVideoService() );

		t_pos pos = pointer->getForm()->getPosition();
		t_size size = pointer->getForm()->getSize();

		IGUIEnvironment *gui = graphics->getGui();

		if ( !listBox ) {
			listBox = gui->addListBox( rect<s32>( 0, 0, 250, 100 ) );
			listBox->setDrawBackground( true );
			listBox->setItemHeight( 30 );

			listBox->addItem( L"Move" );
			listBox->addItem( L"Exit" );
		}

		position2d<s32> currPosition = listBox->getAbsolutePosition().UpperLeftCorner;
		listBox->move( position2d<s32>(
			pos.getX() + size.width - currPosition.X,
			pos.getY() + 20 - currPosition.Y
		));

		listBox->setVisible( true );
		listBox->setSelected( 0 );
		gui->setFocus( listBox );
	}
);

DoActionFunction hideFunction( []( Action *action, GameEntity *entity ) {
	listBox->setVisible( false );
});

WorldMap::WorldMap( const std::string &id ) :
	GameEntity( id )
{
	addState( new StateString( "state:currentCity", "berlin" ) );

	addAction( new ActionLua( *this, "moveRightOnMap", "scripts/move_right_on_map.lua" ) );
	addAction( new ActionLua( *this, "moveLeftOnMap", "scripts/move_left_on_map.lua" ) );
	addAction( new ActionLambda( *this, "showMenu", &showMenuFunction ) );
	addAction( new ActionLambda( *this, "hideMenu", &hideFunction ) );

	CoreServices *services = CoreServices::instance();
	IrrlichtGraphics *graphics =
		dynamic_cast<IrrlichtGraphics*>( services->getVideoService() );

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
}

WorldMap::~WorldMap()
{
}

