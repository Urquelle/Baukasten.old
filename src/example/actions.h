#ifndef ACTIONS_OG1WVP4A
#define ACTIONS_OG1WVP4A

#include <action.h>
#include "states.h"

class ActionLevelUp : public Baukasten::Core::Action {
public:
    ActionLevelUp( Entity &parent ) :
        Action( parent, "levelUp" )
    {
    }

    virtual ~ActionLevelUp()
    {
    }

    void doAction()
    {
        StateLevel *lvl = static_cast<StateLevel*>(
            getParent()->hasState( "stateLevel" )
        );

        if ( lvl )
            lvl->levelUp();
    }

private:
    /* data */
};

class ActionAddExperience : public Baukasten::Core::Action {
public:
    ActionAddExperience( Entity &parent ) :
        Action( parent, "addExperience" )
    {
    }

    virtual ~ActionAddExperience()
    {
    }

    void doAction()
    {
        StateExperience *exp = static_cast<StateExperience*>(
            getParent()->hasState( "stateExperience" )
        );

        if ( exp )
            exp->addExperience( 11 );
    }

private:
    /* data */
};

#endif /* end of include guard: ACTIONS_OG1WVP4A */
