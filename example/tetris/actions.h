#ifndef ACTIONS_J8BEDW58
#define ACTIONS_J8BEDW58

#include "constants.h"

#include <action_lambda.h>
#include <form.h>
#include <generic_state.h>
#include <logical_space.h>
#include <virtual_space.h>

#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace Baukasten;

const int BLOCK_WIDTH = 4, BLOCK_HEIGHT = 40, FIELD_SIZE = 12;
const int LIMIT_TOP = 0, LIMIT_RIGHT = 1, LIMIT_BOTTOM = 2, LIMIT_LEFT = 3;

void setBlockFields( GameEntity *field, int value = SET )
{
	Form *fieldForm = field->getForm();

	auto row = fieldForm->getState<StateInt*>( "block:row" )->getValue();
	auto block = fieldForm->getState<StateIntVector*>( "block:current" )->getValues();
	auto column = fieldForm->getState<StateInt*>( "block:column" )->getValue();
	auto matrixState = fieldForm->getState<StateIntVector*>( "state:field" );
	auto matrix = matrixState->getValues();

	for( int i = 0, j = 0; i < matrix.size(); ++i ) {
		int startBlock = ( row * FIELD_SIZE ) + ( column - 1 );
		int endBlock = ( ( row + 3 ) * FIELD_SIZE ) + ( column + 2 );
		int range = ( i - column + 1 ) % FIELD_SIZE;
		BK_DEBUG( "size: " << block.size() << " startBlock: " << startBlock << " endBlock: " << endBlock << " i: " << i << " range: " << range );
		if ( block.size() && i >= startBlock && i <= endBlock && range >= 0 && range < BLOCK_WIDTH ) {
			int index = ( i - row * FIELD_SIZE - column + 1 ) - ( FIELD_SIZE - BLOCK_WIDTH ) * ( j - row );
			if ( index > 0 && index < 15 && block[ index ] ) {
				matrixState->setValue( i, value );
			}
		}
		j += ( ( i > 0 ) && ( i % FIELD_SIZE ) == 0 ) ? 1 : 0;
	}
}

DoActionFunction nextBlock([]( Action *action, GameEntity *entity ) {
	string blocks[] = { "block:i", "block:j", "block:z", "block:s", "block:l", "block:t", "block:o" };

	srand( time( 0 ) );

	GameEntity *block = entity->getChild( blocks[ rand() % 7 ] );
	GameEntity *field = entity->getParent()->getChild( "entity:field" );
	field->getForm()->getState<StateIntVector*>( "block:current" )->setValues(
		block->getForm()->getState<StateIntVector*>( "state:matrix" )->getValues()
	);

	entity->getParent()->getForm()->addToVSpace( "block:current", block->getForm() );
	field->getState<StateInt*>( "state:column" )->setValue(5);

	setBlockFields( field );
});

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {
	GameEntity *field = entity->getChild( "entity:field" );
	Form *block = entity->getForm()->getVSpace()->getEntity( "block:current" );

	stringstream sLimit;
	sLimit << "state:limit" << block->getState<StateInt*>("state:currentMatrix")->getValue();
	auto limit = block->getState<StateIntVector*>( sLimit.str() );

	StateInt *column = field->getForm()->getState<StateInt*>( "block:column" );
	if ( column->getValue() + limit->getValue( LIMIT_RIGHT ) + 1 < FIELD_SIZE ) {
		setBlockFields( field, CLEAN );
		column->setValue( column->getValue() + 1 );
		setBlockFields( field, IN_MOTION );
	}
});

DoActionFunction moveLeft([]( Action *action, GameEntity *entity ) {
	GameEntity *field = entity->getChild( "entity:field" );
	Form *block = entity->getForm()->getVSpace()->getEntity( "block:current" );

	stringstream sLimit;
	sLimit << "state:limit" << block->getState<StateInt*>("state:currentMatrix")->getValue();
	auto limit = block->getState<StateIntVector*>( sLimit.str() );

	StateInt *column = field->getForm()->getState<StateInt*>( "block:column" );
	if ( column->getValue() - limit->getValue( LIMIT_LEFT ) > 0 ) {
		setBlockFields( field, CLEAN );
		column->setValue( column->getValue() - 1 );
		setBlockFields( field, IN_MOTION );
	}
});

DoActionFunction recalc([]( Action *action, GameEntity *entity ) {
	StateInt *currLine = entity->getForm()->getState<StateInt*>( "state:currentLine" );
	Form *block = entity->getParent()->getForm()->getVSpace()->getEntity( "block:current" );

	StateInt *step = entity->getForm()->getState<StateInt*>( "state:step" );
	step->setValue( step->getValue() + 1 );

	setBlockFields( entity, CLEAN );
	float row = step->getValue() / BLOCK_HEIGHT;
	row += ( step->getValue() % BLOCK_HEIGHT == 0 ) ? 0 : 1;
	entity->getForm()->getState<StateInt*>( "block:row" )->setValue( row );
	setBlockFields( entity, IN_MOTION );

	if ( block ) {
		t_pos pos = block->getPosition();

		int currMatrix = block->getState<StateInt*>( "state:currentMatrix" )->getValue();
		int currRow = ( pos.getY() + 20 ) / BLOCK_HEIGHT;
		int currCol = entity->getState<StateInt*>( "state:column" )->getValue();
		int rows = entity->getState<StateInt*>( "state:rows" )->getValue();

		stringstream sLimit;
		sLimit << "state:limit" << currMatrix;
		auto limit = block->getState<StateIntVector*>( sLimit.str() );

		if ( ( row + 1 + limit->getValue( LIMIT_BOTTOM ) ) < ( rows - 1 )) {
			setBlockFields( entity );
		} else {
			entity->getParent()->getForm()->removeFromVSpace( "block:current" );
			entity->getParent()->getForm()->removeFromLSpace( "block:current" );
			entity->getParent()->getChild( "entity:group" )->invokeAction( "action:nextBlock" );
		}
	}
});

DoneFunction recalcDone([]( const Action *action ) {
	return false;
});

#endif /* end of include guard: ACTIONS_J8BEDW58 */
