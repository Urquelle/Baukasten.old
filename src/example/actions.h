#ifndef ACTIONS_OG1WVP4A
#define ACTIONS_OG1WVP4A

#include <action.h>
#include <generic_state.h>

using namespace Baukasten::Core;

class ActionLevelUp : public Baukasten::Core::Action {
public:
    ActionLevelUp( Entity &source ) :
        Action( source, "levelUp" )
    {
    }

    virtual ~ActionLevelUp()
    {
    }

    void doAction()
    {
        GenericState<int> *lvl = static_cast<GenericState<int>*>(
            getSource()->getState( "level" )
        );

        if ( lvl ) {
            int currentLevel = lvl->getValue();
            lvl->setValue(++currentLevel);
        }
    }

private:
    /* data */
};

class ActionAddExperience : public Baukasten::Core::Action {
public:
    ActionAddExperience( Entity &source ) :
        Action( source, "addExperience" )
    {
    }

    virtual ~ActionAddExperience()
    {
    }

    void doAction()
    {
        GenericState<int> *exp = static_cast<GenericState<int>*>(
            getSource()->getState( "experience" )
        );

        if ( exp ) {
            int expPoints = exp->getValue() + 11;
            exp->setValue( expPoints );

            // check whether the entity has a level state and if
            // we have to increase the level.
            GenericState<int> *lvl = static_cast<GenericState<int>*>(
                getSource()->getState( "level" )
            );

            if ( lvl && expPoints >= 10 && expPoints < 50 && lvl->getValue() < 1 )
                lvl->setValue( lvl->getValue() + 1 );
        }
    }

private:
    /* data */
};

class Hit : public Baukasten::Core::Action {
public:
    Hit( Entity &source ) :
        Action( source, "hit" )
    {
    }

    virtual ~Hit()
    {
    }

    void doAction()
    {
        Entity *target = getTarget();

        if ( !target )
            return;

        GenericState<int> *state = static_cast<GenericState<int>*>(
            target->getState( "hp" )
        );

        if ( !state )
            return;

        state->setValue( state->getValue() - 10 );
    }
};

#endif /* end of include guard: ACTIONS_OG1WVP4A */
