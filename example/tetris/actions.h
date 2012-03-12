#ifndef ACTIONS_J8BEDW58
#define ACTIONS_J8BEDW58

#include "constants.h"

#include "model/ActionLambda"
#include "model/Form"
#include "model/GenericState"
#include "model/LogicalSpace"
#include "model/VirtualSpace"

#include <cstdlib>
#include <ctime>

using namespace Baukasten;

const int BLOCK_WIDTH = 4, BLOCK_HEIGHT = 40, FIELD_SIZE = 12, ROW_COUNT = 18;
const int LIMIT_TOP = 0, LIMIT_RIGHT = 1, LIMIT_BOTTOM = 2, LIMIT_LEFT = 3;

bool
collisionDetected( GameEntity *block, GameEntity *field )
{
	bool retValue = false;
	int rows = field->state<StateInt*>( "state:rows" )->value();
	int fields = FIELD_SIZE * rows;

	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();
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
	Form *fieldForm = field->form();

	auto row = fieldForm->state<StateInt*>( "block:row" )->value();
	auto block = fieldForm->state<StateIntVector*>( "block:current" )->values();
	auto column = fieldForm->state<StateInt*>( "block:column" )->value();
	auto matrixState = fieldForm->state<StateIntVector*>( "state:field" );
	auto matrix = matrixState->values();

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

DoActionFunction nextBlock([]( Action *action, GameEntity *entity ) {
	string blocks[] = { "block:i", "block:j", "block:z", "block:s", "block:l", "block:t", "block:o" };

	srand( time( 0 ) );

	GameEntity *block = 0;
	GameEntity *field = entity->parent()->child( "entity:field" );
	GameEntity *nextBlock = entity->child( blocks[ rand() % 7 ] );

	if ( field->form()->lSpace()->hasEntity( "block:next" ) ) {
		block = field->form()->lSpace()->entity( "block:next" );
	} else {
		block = entity->child( blocks[ rand() % 7 ] );
	}

	field->form()->state<StateIntVector*>( "block:current" )->setValues(
		block->form()->state<StateIntVector*>( "state:matrix" )->values()
	);

	entity->parent()->form()->addToLSpace( "block:current", block );
	field->state<StateInt*>( "state:column" )->setValue(5);
	field->form()->state<StateInt*>( "block:column" )->setValue( 5 );

	field->form()->removeFromLSpace( "block:next" );
	field->form()->removeFromVSpace( "block:next" );
	field->form()->addToLSpace( "block:next", nextBlock );
	field->form()->addToVSpace( "block:next", nextBlock->form() );
	nextBlock->form()->setPosition( { 800, 40, 0 } );

	setBlockFields( field, IN_MOTION );

	if ( collisionDetected( block, field ) ) {
		entity->parent()->invokeAction( "action:gameOver", field );
	}
});

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {

	auto gamePaused = entity->state<StateBool*>( "state:pause" );
	if ( gamePaused && gamePaused->value() ) return; // do nothing on pause

	GameEntity *field = entity->child( "entity:field" );
	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();

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

	StateInt *column = field->form()->state<StateInt*>( "block:column" );
	if ( !v ) {
		setBlockFields( field, CLEAN );
		column->setValue( column->value() + 1 );
		setBlockFields( field, IN_MOTION );
	}
});

DoActionFunction moveLeft([]( Action *action, GameEntity *entity ) {

	auto gamePaused = entity->state<StateBool*>( "state:pause" );
	if ( gamePaused && gamePaused->value() ) return; // do nothing on pause

	GameEntity *field = entity->child( "entity:field" );
	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();

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

	StateInt *column = field->form()->state<StateInt*>( "block:column" );
	if ( !v ) {
		setBlockFields( field, CLEAN );
		column->setValue( column->value() - 1 );
		setBlockFields( field, IN_MOTION );
	}
});

DoActionFunction recalc([]( Action *action, GameEntity *field ) {

	auto gamePaused = field->parent()->state<StateBool*>( "state:pause" );
	if ( gamePaused && gamePaused->value() ) return; // do nothing on pause

	GameEntity *block = field->parent()->form()->lSpace()->entity( "block:current" );

	StateInt *step = field->form()->state<StateInt*>( "state:step" );
	step->setValue( step->value() + 1 );

	setBlockFields( field, CLEAN );
	float row = step->value() / BLOCK_HEIGHT;
	row += ( step->value() % BLOCK_HEIGHT == 0 ) ? 0 : 1;
	field->form()->state<StateInt*>( "block:row" )->setValue( row );
	setBlockFields( field, IN_MOTION );

	if ( block ) {
		vec3<float> pos = block->form()->position();

		int currMatrix = block->form()->state<StateInt*>( "state:currentMatrix" )->value();
		int rows = field->state<StateInt*>( "state:rows" )->value();

		if ( collisionDetected( block, field ) ) {
			field->invokeAction( "action:clearCompleteRows" );

			setBlockFields( field, SET );
			step->setValue( 0 );

			field->form()->state<StateInt*>( "block:row" )->setValue( 0 );
			field->parent()->form()->removeFromLSpace( "block:current" );
			field->parent()->child( "entity:group" )->invokeAction( "action:nextBlock" );
		}
	}
});

DoActionFunction clearCompleteRows([]( Action *action, GameEntity *entity ) {
	GameEntity *field = action->source();
	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();
	auto score = field->parent()->child( "entity:score" );

	int setBlocksCount = 0;
	int points = 0;
	int currRow = ROW_COUNT - 1, prevRow = ROW_COUNT - 1;
	vector<int> completeRows;
	for ( int i = ( FIELD_SIZE * ROW_COUNT ) - 1; i >= 0; --i ) {
		currRow = (int)( i / FIELD_SIZE );

		// if still in the same row and this block is set
		if ( currRow == prevRow && fieldMatrix[ i ] == SET ) {
			setBlocksCount++;

		// if the next row's reached -- remember we go up the field, from 17 down to 0 ...
		} else if( currRow < prevRow ) {
			// ... and the row was complete
			if ( setBlocksCount == FIELD_SIZE ) {
				completeRows.push_back( prevRow );

			// ... else collect the points
			} else if ( completeRows.size() > 0 ) {
				// add new points
				score->state<StateInt*>( "state:linesCleared" )->setValue( completeRows.size() );
				score->invokeAction( "action:collectPoints" );

				// clear the rows
				int shiftBy = FIELD_SIZE * ( completeRows[0] - completeRows[completeRows.size() - 1] + 1 );
				int shiftTo = completeRows[0] * FIELD_SIZE + FIELD_SIZE - 1;
				int shiftFrom = ( completeRows[ completeRows.size() - 1 ] - 1 ) * FIELD_SIZE + FIELD_SIZE - 1;

				for( ; shiftFrom >= 0; --shiftTo, --shiftFrom ) {
					if( fieldMatrix[ shiftTo ] != IN_MOTION && fieldMatrix[ shiftFrom ] != IN_MOTION ) {
						fieldMatrix[ shiftTo ] = fieldMatrix[ shiftFrom ];
					}
				}

				// set matrix
				field->form()->state<StateIntVector*>( "state:field" )->setValues( fieldMatrix );

				completeRows.clear();
			}

			setBlocksCount = 0;

			if ( fieldMatrix[ i ] == SET )
				setBlocksCount++;
		}
		prevRow = currRow;
	}
});

DoneFunction recalcDone([]( const Action *action ) {
	return false;
});

DoActionFunction collectPoints([]( Action *action, GameEntity *entity ) {
	auto score = action->source()->state<StateInt*>( "state:score" );
	auto lines = action->source()->state<StateInt*>( "state:linesCleared" );
	int points = 0;

	if ( lines->value() == 4 )
		points = 1000;
	else
		points = lines->value() * 50;

	lines->setValue( 0 );
	score->setValue( score->value() + points );
	action->source()->form()->state<StateInt*>( "state:score" )->setValue( score->value() );
});

#endif /* end of include guard: ACTIONS_J8BEDW58 */
