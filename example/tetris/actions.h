#ifndef ACTIONS_J8BEDW58
#define ACTIONS_J8BEDW58

#include <action_lambda.h>
#include <form.h>
#include <generic_state.h>
#include <virtual_space.h>

#include <cstdlib>
#include <ctime>

using namespace Baukasten;

const int BLOCK_WIDTH = 40, BLOCK_HEIGHT = 40;

DoActionFunction nextBlock([]( Action *action, GameEntity *entity ) {
	string blocks[] = { "block:i", "block:j", "block:z", "block:s", "block:l", "block:t", "block:o" };

	srand( time( 0 ) );

	GameEntity *block = entity->getChild( blocks[ rand() % 7 ] );
	GameEntity *field = entity->getParent()->getChild( "entity:field" );

	entity->getParent()->getForm()->addToLSpace( block );
	entity->getParent()->getForm()->addToVSpace( "block:current", block->getForm() );
	block->getForm()->setPosition( { 400, 20, 0 } );
});

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {
	Form *form = action->getSource()->getForm()->getVSpace()->getEntity( "block:current" );
	t_pos currPos = form->getPosition();
	t_pos nextPos( { currPos.getX() + BLOCK_WIDTH, currPos.getY(), currPos.getZ() } );

	if ( nextPos.getX() < 640 ) {
		form->setPosition( nextPos );
	}
});

DoActionFunction moveLeft([]( Action *action, GameEntity *entity ) {
	Form *form = action->getSource()->getForm()->getVSpace()->getEntity( "block:current" );
	t_pos currPos = form->getPosition();
	t_pos nextPos( { currPos.getX() - BLOCK_WIDTH, currPos.getY(), currPos.getZ() } );

	if ( nextPos.getX() > 200 ) {
		form->setPosition( nextPos );
	}
});

#endif /* end of include guard: ACTIONS_J8BEDW58 */
