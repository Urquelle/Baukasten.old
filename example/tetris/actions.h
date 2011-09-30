#ifndef ACTIONS_J8BEDW58
#define ACTIONS_J8BEDW58

#include <action_lambda.h>
#include <form.h>
#include <generic_state.h>
#include <virtual_space.h>

#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace Baukasten;

const int BLOCK_WIDTH = 40, BLOCK_HEIGHT = 40;
const int LIMIT_TOP = 0, LIMIT_RIGHT = 1, LIMIT_BOTTOM = 2, LIMIT_LEFT = 3;

DoActionFunction nextBlock([]( Action *action, GameEntity *entity ) {
	string blocks[] = { "block:i", "block:j", "block:z", "block:s", "block:l", "block:t", "block:o" };

	srand( time( 0 ) );

	GameEntity *block = entity->getChild( blocks[ rand() % 7 ] );
	GameEntity *field = entity->getParent()->getChild( "entity:field" );

	entity->getParent()->getForm()->addToLSpace( block );
	entity->getParent()->getForm()->addToVSpace( "block:current", block->getForm() );
	block->getForm()->setPosition( { 400, 20, 0 } );

	field->getState<StateInt*>( "state:column" )->setValue(6);
});

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {
	Form *form = action->getSource()->getForm()->getVSpace()->getEntity( "block:current" );
	GameEntity *field = entity->getChild( "entity:field" );

	Form *block = entity->getForm()->getVSpace()->getEntity( "block:current" );

	stringstream sLimit;
	sLimit << "state:limit" << block->getState<StateInt*>("state:currentMatrix")->getValue();
	auto limit = block->getState<StateIntVector*>( sLimit.str() );

	StateInt *column = field->getState<StateInt*>( "state:column" );

	if ( column->getValue() + limit->getValue( LIMIT_RIGHT ) < 13 ) {
		t_pos currPos = form->getPosition();
		t_pos nextPos( { currPos.getX() + BLOCK_WIDTH, currPos.getY(), currPos.getZ() } );

		column->setValue( column->getValue() + 1 );
		form->setPosition( nextPos );
	}
});

DoActionFunction moveLeft([]( Action *action, GameEntity *entity ) {
	Form *form = action->getSource()->getForm()->getVSpace()->getEntity( "block:current" );
	GameEntity *field = entity->getChild( "entity:field" );

	Form *block = entity->getForm()->getVSpace()->getEntity( "block:current" );

	stringstream sLimit;
	sLimit << "state:limit" << block->getState<StateInt*>("state:currentMatrix")->getValue();
	auto limit = block->getState<StateIntVector*>( sLimit.str() );

	StateInt *column = field->getState<StateInt*>( "state:column" );

	if ( column->getValue() - limit->getValue( LIMIT_LEFT ) > 0 ) {
		t_pos currPos = form->getPosition();
		t_pos nextPos( { currPos.getX() - BLOCK_WIDTH, currPos.getY(), currPos.getZ() } );

		column->setValue( column->getValue() - 1 );
		form->setPosition( nextPos );
	}
});

DoActionFunction recalc([]( Action *action, GameEntity *entity ) {
	StateInt *currLine = entity->getForm()->getState<StateInt*>( "state:currentLine" );
	Form *block = entity->getParent()->getForm()->getVSpace()->getEntity( "block:current" );

	if ( block ) {
		t_pos pos = block->getPosition();
		int currBlockLine = pos.getY() / BLOCK_HEIGHT;

		if ( currBlockLine < 18 )
			block->setPosition( { pos.getX(), pos.getY() + 1, 0 } );
	}
});

DoneFunction recalcDone([]( const Action *action ) {
	return false;
});

#endif /* end of include guard: ACTIONS_J8BEDW58 */
