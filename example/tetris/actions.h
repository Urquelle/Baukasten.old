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

const int BLOCK_WIDTH = 4, BLOCK_HEIGHT = 40, FIELD_SIZE = 12, ROW_COUNT = 18;
const int LIMIT_TOP = 0, LIMIT_RIGHT = 1, LIMIT_BOTTOM = 2, LIMIT_LEFT = 3;

bool
collisionDetected( GameEntity *block, GameEntity *field )
{
	bool retValue = false;
	int rows = field->getState<StateInt*>( "state:rows" )->getValue();
	int fields = FIELD_SIZE * rows;

	auto fieldMatrix = field->getForm()->getState<StateIntVector*>( "state:field" )->getValues();
	for ( int i = 0; i < fields; ++i ) {
		if ( fieldMatrix[ i ] == IN_MOTION && ( ( i + FIELD_SIZE ) < fields ) && ( fieldMatrix[ i + FIELD_SIZE ] == SET ) ) {
			retValue = true;
		}

		if ( fieldMatrix[ i ] == IN_MOTION && ( i + FIELD_SIZE ) > ( fields - 1 ) ) {
			retValue = true;
		}
	}

	return retValue;
}

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
		j = (int)( i / FIELD_SIZE );

		if ( block.size() && i >= startBlock && i <= endBlock && range >= 0 && range < BLOCK_WIDTH ) {
			int index = ( i - row * FIELD_SIZE - column + 1 ) - ( FIELD_SIZE - BLOCK_WIDTH ) * ( j - row );

			// skip iteration if index outside valid range
			if ( index < 0 || index > 15 )
				continue;

			// skip iteration if block is about to be cleaned or set to IN_MOTION, where
			// it is already set to SET
			if ( matrix[ i ] == SET && ( CLEAN == value || IN_MOTION == value ) )
				continue;

			if ( ( IN_MOTION == value || SET == value ) && block[ index ] || CLEAN == value )
				matrixState->setValue( i, value );
		}
	}
}

DoActionFunction pauseGame([]( Action *action, GameEntity *entity ) {
	entity->getState<StateBool*>( "state:pause" )->setValue(
		!entity->getState<StateBool*>( "state:pause" )->getValue()
	);
});

DoActionFunction gameOver([]( Action *action, GameEntity *field ) {
	field->dropAction( "action:recalculate" );
});

DoActionFunction nextBlock([]( Action *action, GameEntity *entity ) {
	string blocks[] = { "block:i", "block:j", "block:z", "block:s", "block:l", "block:t", "block:o" };

	srand( time( 0 ) );

	GameEntity *block = 0;
	GameEntity *field = entity->getParent()->getChild( "entity:field" );
	GameEntity *nextBlock = entity->getChild( blocks[ rand() % 7 ] );

	if ( field->getForm()->getLSpace()->hasEntity( "block:next" ) ) {
		block = field->getForm()->getLSpace()->getEntity( "block:next" );
	} else {
		block = entity->getChild( blocks[ rand() % 7 ] );
	}

	field->getForm()->getState<StateIntVector*>( "block:current" )->setValues(
		block->getForm()->getState<StateIntVector*>( "state:matrix" )->getValues()
	);

	entity->getParent()->getForm()->addToLSpace( "block:current", block );
	field->getState<StateInt*>( "state:column" )->setValue(5);
	field->getForm()->getState<StateInt*>( "block:column" )->setValue( 5 );

	field->getForm()->removeFromLSpace( "block:next" );
	field->getForm()->removeFromVSpace( "block:next" );
	field->getForm()->addToLSpace( "block:next", nextBlock );
	field->getForm()->addToVSpace( "block:next", nextBlock->getForm() );
	nextBlock->getForm()->setPosition( { 800, 40, 0 } );

	setBlockFields( field, IN_MOTION );

	if ( collisionDetected( block, field ) ) {
		entity->getParent()->invokeAction( "action:gameOver", field );
	}
});

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {

	auto gamePaused = entity->getState<StateBool*>( "state:pause" );
	if ( gamePaused && gamePaused->getValue() ) return; // do nothing on pause

	GameEntity *field = entity->getChild( "entity:field" );
	auto fieldMatrix = field->getForm()->getState<StateIntVector*>( "state:field" )->getValues();

	bool v = false;
	for ( int i = 0; i < ( FIELD_SIZE * ROW_COUNT ); ++i ) {
		if ( v ) break;
		if ( fieldMatrix[ i ] == IN_MOTION ) {
			// either the right field border is reached ...
			if ( ( i % FIELD_SIZE ) == ( FIELD_SIZE - 1 ) )
				v = true;
			// ... or there are some set blocks in the way
			if ( ( i + 1 ) % FIELD_SIZE > 0 && ( ( i + 1 ) <= ( FIELD_SIZE * ROW_COUNT ) ) && fieldMatrix[ i + 1 ] == SET )
				v = true;
		}
	}

	StateInt *column = field->getForm()->getState<StateInt*>( "block:column" );
	if ( !v ) {
		setBlockFields( field, CLEAN );
		column->setValue( column->getValue() + 1 );
		setBlockFields( field, IN_MOTION );
	}
});

DoActionFunction moveLeft([]( Action *action, GameEntity *entity ) {

	auto gamePaused = entity->getState<StateBool*>( "state:pause" );
	if ( gamePaused && gamePaused->getValue() ) return; // do nothing on pause

	GameEntity *field = entity->getChild( "entity:field" );
	auto fieldMatrix = field->getForm()->getState<StateIntVector*>( "state:field" )->getValues();

	bool v = false;
	for ( int i = 0; i < ( FIELD_SIZE * ROW_COUNT ); ++i ) {
		if ( v ) break;
		if ( fieldMatrix[ i ] == IN_MOTION ) {
			// either the left field border is reached ...
			if ( ( i % FIELD_SIZE ) == 0 )
				v = true;
			// ... or there are some set blocks in the way
			if ( ( ( i - 1 ) % FIELD_SIZE ) < ( FIELD_SIZE - 1 ) && ( ( i - 1 ) >= 0 ) && fieldMatrix[ i - 1 ] == SET )
				v = true;
		}
	}

	StateInt *column = field->getForm()->getState<StateInt*>( "block:column" );
	if ( !v ) {
		setBlockFields( field, CLEAN );
		column->setValue( column->getValue() - 1 );
		setBlockFields( field, IN_MOTION );
	}
});

DoActionFunction recalc([]( Action *action, GameEntity *entity ) {

	auto gamePaused = entity->getParent()->getState<StateBool*>( "state:pause" );
	if ( gamePaused && gamePaused->getValue() ) return; // do nothing on pause

	GameEntity *block = entity->getParent()->getForm()->getLSpace()->getEntity( "block:current" );

	StateInt *step = entity->getForm()->getState<StateInt*>( "state:step" );
	step->setValue( step->getValue() + 1 );

	setBlockFields( entity, CLEAN );
	float row = step->getValue() / BLOCK_HEIGHT;
	row += ( step->getValue() % BLOCK_HEIGHT == 0 ) ? 0 : 1;
	entity->getForm()->getState<StateInt*>( "block:row" )->setValue( row );
	setBlockFields( entity, IN_MOTION );

	if ( block ) {
		t_pos pos = block->getForm()->getPosition();

		int currMatrix = block->getForm()->getState<StateInt*>( "state:currentMatrix" )->getValue();
		int rows = entity->getState<StateInt*>( "state:rows" )->getValue();

		if ( collisionDetected( block, entity ) ) {
			setBlockFields( entity, SET );
			step->setValue( 0 );

			entity->getForm()->getState<StateInt*>( "block:row" )->setValue( 0 );
			entity->getParent()->getForm()->removeFromLSpace( "block:current" );
			entity->getParent()->getChild( "entity:group" )->invokeAction( "action:nextBlock" );
		}
	}
});

DoneFunction recalcDone([]( const Action *action ) {
	return false;
});

#endif /* end of include guard: ACTIONS_J8BEDW58 */
