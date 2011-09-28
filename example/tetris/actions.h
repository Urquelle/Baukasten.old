#ifndef ACTIONS_J8BEDW58
#define ACTIONS_J8BEDW58

#include <action_lambda.h>
#include <form.h>
#include <virtual_space.h>

using namespace Baukasten;

DoActionFunction moveRight([]( Action *action, GameEntity *entity ) {
	Form *form = action->getSource()->getForm()->getVSpace()->getEntity( "block:current" );
	t_pos currPos = form->getPosition();
	t_pos nextPos( { currPos.getX() + 40, currPos.getY(), currPos.getZ() } );

	if ( nextPos.getX() < 640 ) {
		form->setPosition( nextPos );
	}
});

DoActionFunction moveLeft([]( Action *action, GameEntity *entity ) {
	Form *form = action->getSource()->getForm()->getVSpace()->getEntity( "block:current" );
	t_pos currPos = form->getPosition();
	t_pos nextPos( { currPos.getX() - 40, currPos.getY(), currPos.getZ() } );

	if ( nextPos.getX() > 200 ) {
		form->setPosition( nextPos );
	}
});

#endif /* end of include guard: ACTIONS_J8BEDW58 */
