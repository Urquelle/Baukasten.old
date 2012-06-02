#ifndef ACTIONS_J8BEDW58
#define ACTIONS_J8BEDW58

#include "constants.h"

#include "core/TimerInterface"
#include "core/Timer"
#include "math/Random"
#include "model/ActionLambda"
#include "model/Form"
#include "model/GenericState"
#include "model/LogicalSpace"
#include "model/VirtualSpace"

using namespace Baukasten;

bool
collisionDetected( GameEntity *block, GameEntity *field )
{
	bool retValue = false;
	int rows = field->state<StateInt*>( "state:rows" )->value();
	int fields = FIELD_WIDTH * rows;

	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();
	for ( int i = 0; i < fields; ++i ) {
		if ( fieldMatrix[ i ] == IN_MOTION && ( ( i + FIELD_WIDTH ) < fields ) && ( fieldMatrix[ i + FIELD_WIDTH ] == SET ) ) {
			retValue = true;
		}

		if ( fieldMatrix[ i ] == IN_MOTION && ( i + FIELD_WIDTH ) > ( fields - 1 ) ) {
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
		int startBlock = ( row * FIELD_WIDTH ) + ( column - 1 );
		int endBlock = ( ( row + 3 ) * FIELD_WIDTH ) + ( column + 2 );
		int range = ( i - column + 1 ) % FIELD_WIDTH;
		j = (int)( i / FIELD_WIDTH );

		if ( block.size() && i >= startBlock && i <= endBlock && range >= 0 && range < BLOCK_WIDTH ) {
			int index = ( i - row * FIELD_WIDTH - column + 1 ) - ( FIELD_WIDTH - BLOCK_WIDTH ) * ( j - row );

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

	u32 iNext = (int)( Random::random() * 10 );
	u32 iANext = (int)( Random::random() * 10 );

	GameEntity *block = 0;
	GameEntity *field = entity->parent()->child( "entity:field" );
	GameEntity *nextBlock = entity->child( blocks[ iNext % 7 ] );
	GameEntity *preview = field->parent()->child( "entity:preview" );

	if ( field->form()->lSpace()->hasEntity( "block:next" ) ) {
		block = field->form()->lSpace()->entity( "block:next" );
	} else {
		block = entity->child( blocks[ iANext % 7 ] );
	}

	field->form()->state<StateIntVector*>( "block:current" )->setValues(
		block->form()->state<StateIntVector*>( "state:matrix" )->values()
	);

	entity->parent()->form()->addToLSpace( "block:current", block );
	field->state<StateInt*>( "state:column" )->setValue(5);
	field->form()->state<StateInt*>( "block:column" )->setValue( 5 );

	field->form()->removeFromLSpace( "block:next" );
	field->form()->addToLSpace( "block:next", nextBlock );

	preview->form()->state<StateIntVector*>( "state:matrix" )->setValues(
		nextBlock->form()->state<StateIntVector*>( "state:matrix1" )->values()
	);

	setBlockFields( field, IN_MOTION );

	if ( collisionDetected( block, field ) ) {
		entity->parent()->invokeAction( "action:gameOver", field );
	}
});

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {

	if ( TimerInterface::instance()->timer( "game:main" ).isPaused() )
		return; // do nothing on pause

	GameEntity *field = entity->child( "entity:field" );
	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();

	bool v = false;
	for ( int i = 0; i < ( FIELD_WIDTH * FIELD_HEIGHT ); ++i ) {
		if ( v ) break;
		if ( fieldMatrix[ i ] == IN_MOTION ) {
			// either the right field border is reached ...
			if ( ( i % FIELD_WIDTH ) == ( FIELD_WIDTH - 1 ) )
				v = true;
			// ... or there are some set blocks in the way
			if ( ( i + 1 ) % FIELD_WIDTH > 0 && ( ( i + 1 ) <= ( FIELD_WIDTH * FIELD_HEIGHT ) ) && fieldMatrix[ i + 1 ] == SET )
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

	if ( TimerInterface::instance()->timer( "game:main" ).isPaused() )
		return; // do nothing on pause

	GameEntity *field = entity->child( "entity:field" );
	auto fieldMatrix = field->form()->state<StateIntVector*>( "state:field" )->values();

	bool v = false;
	for ( int i = 0; i < ( FIELD_WIDTH * FIELD_HEIGHT ); ++i ) {
		if ( v ) break;
		if ( fieldMatrix[ i ] == IN_MOTION ) {
			// either the left field border is reached ...
			if ( ( i % FIELD_WIDTH ) == 0 )
				v = true;
			// ... or there are some set blocks in the way
			if ( ( ( i - 1 ) % FIELD_WIDTH ) < ( FIELD_WIDTH - 1 ) && ( ( i - 1 ) >= 0 ) && fieldMatrix[ i - 1 ] == SET )
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

	Timer &t = TimerInterface::instance()->timer( "game:main" );

	auto game = field->parent();

	GameEntity *block = field->parent()->form()->lSpace()->entity( "block:current" );

	StateFloat *speed = game->state<StateFloat*>( "state:speed" );
	StateFloat *time = field->form()->state<StateFloat*>( "state:time" );
	setBlockFields( field, CLEAN );
	if ( t.time() - time->value() >= speed->value() ) {
		field->form()->state<StateInt*>( "block:row" )->setValue(
			field->form()->state<StateInt*>( "block:row" )->value() + 1
		);

		time->setValue( t.time() );
	}
	setBlockFields( field, IN_MOTION );

	if ( block ) {
		u32 currMatrix = block->form()->state<StateInt*>( "state:currentMatrix" )->value();
		u32 rows = field->state<StateInt*>( "state:rows" )->value();

		if ( collisionDetected( block, field ) ) {
			field->invokeAction( "action:clearCompleteRows" );

			setBlockFields( field, SET );

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
	int currRow = FIELD_HEIGHT - 1, prevRow = FIELD_HEIGHT - 1;
	vector<int> completeRows;
	for ( int i = ( FIELD_WIDTH * FIELD_HEIGHT ) - 1; i >= 0; --i ) {
		currRow = (int)( i / FIELD_WIDTH );

		// if still in the same row and this block is set
		if ( currRow == prevRow && fieldMatrix[ i ] == SET ) {
			setBlocksCount++;

		// if the next row's reached -- remember we go up the field, from 17 down to 0 ...
		} else if( currRow < prevRow ) {
			// ... and the row was complete
			if ( setBlocksCount == FIELD_WIDTH ) {
				completeRows.push_back( prevRow );

			// ... else collect the points
			} else if ( completeRows.size() > 0 ) {
				// add new points
				score->state<StateInt*>( "state:linesCleared" )->setValue( completeRows.size() );
				score->invokeAction( "action:collectPoints" );

				// clear the rows
				int shiftBy = FIELD_WIDTH * ( completeRows[0] - completeRows[completeRows.size() - 1] + 1 );
				int shiftTo = completeRows[0] * FIELD_WIDTH + FIELD_WIDTH - 1;
				int shiftFrom = ( completeRows[ completeRows.size() - 1 ] - 1 ) * FIELD_WIDTH + FIELD_WIDTH - 1;

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
