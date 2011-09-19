#include "menu_form.h"

#include <irrlicht/irrlicht_graphics.h>

#include <irrlicht/irrlicht.h>

using namespace Baukasten;

using namespace irr;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;
using namespace video;

MenuForm::MenuForm( const std::string &id, IGraphics *graphics ) :
	IrrlichtForm( id, dynamic_cast<IrrlichtGraphics*>( graphics ) ),
	mMenu( 0 )
{
	mMenu = getGraphics()->getGui()->addListBox( rect<s32>( 0, 0, 250, 100 ) );

	mMenu->setDrawBackground( true );
	mMenu->setItemHeight( 30 );

	mMenu->addItem( L"Move" );
	mMenu->addItem( L"Abort" );
	mMenu->addItem( L"Exit" );

	setVisible( false );
}

MenuForm::~MenuForm()
{
}

void MenuForm::render()
{
	t_pos pos = getPosition();

	position2d<s32> currPosition = mMenu->getAbsolutePosition().UpperLeftCorner;
	mMenu->move( position2d<s32>(
		pos.getX() - currPosition.X,
		pos.getY() - currPosition.Y
	));

	getGraphics()->getGui()->setFocus( mMenu );
}

void MenuForm::setVisible( bool visible )
{
	if ( visible )
		mMenu->setSelected( 0 );
	mMenu->setVisible( visible );
}

int MenuForm::getCurrentIndex() const
{
	return mMenu->getSelected();
}

