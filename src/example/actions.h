#ifndef ACTIONS_OG1WVP4A
#define ACTIONS_OG1WVP4A

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

    void doAction()
    {
		// remove the action from the execution queue
		getSource()->dropAction( getId() );

		Unit *target = static_cast<Unit*>(getTarget());

		if ( target ) {
			levelUp( target );
		}

		EntityList targetList = getTargetList();

		if ( !target && targetList.empty() )
			levelUp( static_cast<Unit*>(getSource() ) );
    }

	void levelUp( Unit *unit )
	{
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

    void doAction()
    {
		// remove the action from the execution queue
		getSource()->dropAction( getId() );

		Unit *target = static_cast<Unit*>(getSource());

        if ( target ) {
			addExperience( target );
        }
    }

	void addExperience( Unit *unit )
	{
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

	void doAction()
	{
		// remove the action from the execution queue
		getSource()->dropAction( getId() );

		Unit *target = static_cast<Unit*>( getTarget() );

		if ( target ) {
			die( target );
		}

		EntityList targetList = getTargetList();
		EntityList::iterator it;

		for ( it = targetList.begin(); it != targetList.end(); ++it ) {
			die( static_cast<Unit*>(*it) );
		}

		if ( targetList.empty() ) {
			die( static_cast<Unit*>(getSource()) );
		}
	}

	void die( Unit *unit )
	{
		std::cout << unit->getName() << ": it's ... over ... at last ... Hnnnnnnng" << std::endl;
	}
};

class HitAction : public Baukasten::Core::Action {
public:
    HitAction( Entity &source ) :
        Action( source, "hit" )
    {
    }

    virtual ~HitAction()
    {
    }

    void doAction()
    {
		// remove the action from the execution queue
		getSource()->dropAction( getId() );

        Unit *target = static_cast<Unit*>(getTarget());

        if ( target ) {
			hit( target );
		}

		EntityList targetList = getTargetList();
		EntityList::iterator it = targetList.begin();

		if ( !targetList.empty() ) {
			while ( it != targetList.end() ) {
				hit( static_cast<Unit*>(*it) );
				it++;
			}
		}
    }

	void hit( Unit *unit )
	{
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
		std::cout << source->getName() << " just hit " << unit->getName() << " ... Oouch!" << std::endl;

		if ( state->getValue() <= 0 ) {
			state->setValue( 0 );

			// call the die action ... MUAHAHAHAHA
			unit->invokeAction( "die" );
			unit->runActions();
		}
	}
};


#endif /* end of include guard: ACTIONS_OG1WVP4A */
