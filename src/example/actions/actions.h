#ifndef ACTIONS_OG1WVP4A
#define ACTIONS_OG1WVP4A

#include "entities/entities.h"

#include <action.h>
#include <generic_state.h>

#include <iostream>

using namespace Baukasten;

class UpdateState : public Action {
public:
	UpdateState( GameEntity &source ) :
		Action( source, "updateState" )
	{
	}

	virtual ~UpdateState()
	{
	}

	void doAction( GameEntity *entity )
	{
		string name = entity->getState<StateString*>( "name" )->getValue();

		if ( name == "gomez" ) {
			if ( entity->getState<StateInt*>( "hp" )->getValue() == 0 ) {
				cout << "gomez, our great leader ... is ... dead!!!1!" << endl;
				cout << "GAME OVER!" << endl;
				getSource()->getState<StateBool*>( "keepRunning" )->setValue( false );
			}
		}
	}

private:
	/* data */
};

#endif /* end of include guard: ACTIONS_OG1WVP4A */
