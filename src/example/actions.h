#ifndef ACTIONS_OG1WVP4A
#define ACTIONS_OG1WVP4A

#include "entities.h"

#include <action.h>
#include <generic_state.h>

#include <iostream>

using namespace Baukasten;

class LevelUpAction : public Action {
public:
    LevelUpAction( Unit &source ) :
        Action( source, "levelUp" )
    {
    }

    virtual ~LevelUpAction()
    {
    }

	void doAction( GameEntity *entity )
	{
		Unit *unit = static_cast<Unit*>( entity );

		GenericState<int> *state = static_cast<GenericState<int>*>(unit->getState( "level" ));
		state->setValue( state->getValue() + 1 );
		std::cout << unit->getName() << " reached  Level " << state->getValue() << "! Ooohh ... shiny!" << std::endl;
	}

private:
    /* data */
};

class AddExperienceAction : public Action {
public:
    AddExperienceAction( Unit &source ) :
        Action( source, "addExperience" )
    {
    }

    virtual ~AddExperienceAction()
    {
    }

	void doAction( GameEntity *entity )
	{
		Unit *unit = static_cast<Unit*>( entity );

        GenericState<int> *exp = static_cast<GenericState<int>*>(
            getSource()->getState( "experience" )
        );

		int pOld = exp->getValue();
		int pNew = pOld + 10;
		exp->setValue( pNew );

		std::cout << unit->getName() << ": just scored 10 exp points! (" << exp->getValue() << ")" << std::endl;

		// level 1
		if ( pOld < 10 && pNew >= 10 ) {
			unit->invokeAction( "levelUp" );
			unit->runActions();
		}

		// level 2
		if ( pOld < 30 && pNew >= 30 ) {
			unit->invokeAction( "levelUp" );
			unit->runActions();
		}

		// level 3
		if ( pOld < 50 && pNew >= 50 ) {
			unit->invokeAction( "levelUp" );
			unit->runActions();
		}
	}

private:
    /* data */
};

class DieAction : public Action {
public:
	DieAction( Unit &source ) :
		Action( source, "die" )
	{
	}

	virtual ~DieAction()
	{
	}

	void doAction( GameEntity *entity )
	{
		Unit *unit = static_cast<Unit*>(entity);

		std::cout << unit->getName() << ": it's ... over ... at last ... Hnnnnnnng" << std::endl;
	}
};

class MoveAction : public Action {
public:
    MoveAction( GameEntity &source ) :
        Action( source, "move" )
    {
    }

    virtual ~MoveAction()
    {
    }

	void doAction( GameEntity *entity )
	{
		Unit *unit = static_cast<Unit*>(entity);
		std::cout << unit->getName() << " just moved to somewhere else." << std::endl;
	}
};

#endif /* end of include guard: ACTIONS_OG1WVP4A */
