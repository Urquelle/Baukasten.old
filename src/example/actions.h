#ifndef ACTIONS_OG1WVP4A
#define ACTIONS_OG1WVP4A

#include "entities.h"

#include <action.h>
#include <generic_state.h>

#include <iostream>

using namespace Baukasten::Core;

class LevelUpAction : public Baukasten::Core::Action {
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

class AddExperienceAction : public Baukasten::Core::Action {
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

class DieAction : public Baukasten::Core::Action {
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

class HitAction : public Baukasten::Core::Action {
public:
    HitAction( GameEntity &source ) :
        Action( source, "hit" )
    {
    }

    virtual ~HitAction()
    {
    }

	void doAction( GameEntity *entity )
	{
		Unit *unit = static_cast<Unit*>(entity);

		GenericState<int> *state = static_cast<GenericState<int>*>(
			unit->getState( "hp" )
		);

		if ( !state )
			return;

		Unit *source = static_cast<Unit*>( getSource() );

		if ( source != unit ) {
			source->invokeAction( "addExperience" );
			source->runActions();
		}

		state->setValue( state->getValue() - 10 );
		std::cout << source->getName() << "(" << source->getSex() << ") just hit " << unit->getName() << " ... Oouch!" << std::endl;

		if ( state->getValue() <= 0 ) {
			state->setValue( 0 );

			// call the die action ... MUAHAHAHAHA
			unit->invokeAction( "die" );
			unit->runActions();
		}
	}
};

class MoveAction : public Baukasten::Core::Action {
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
