#include "states.h"
#include "actions.h"

StateName::StateName( Entity &parent, const std::string &unitName ) :
    Baukasten::Core::State( parent, "stateName" ),
    mUnitName( unitName )
{
}

StateName::~StateName() {}

const std::string StateName::getName() const
{
    return mUnitName;
}

void StateName::setName( const std::string &name )
{
    mUnitName = name;
}

StateLevel::StateLevel( Entity &parent, const int level ) :
    Baukasten::Core::State( parent, "stateLevel" ),
    mLevel( level )
{
}

StateLevel::~StateLevel() {}

int StateLevel::getLevel() const
{
    return mLevel;
}

void StateLevel::levelUp()
{
    mLevel++;
}

StateExperience::StateExperience( Entity &parent, const int experience) :
    Baukasten::Core::State( parent, "stateExperience" ),
    mExperience( experience)
{
}

StateExperience::~StateExperience() {}

int StateExperience::getExperience() const
{
    return mExperience;
}

void StateExperience::addExperience( int exp )
{
    mExperience += exp;
    int lvl = 0;

    // get the levelUp action from the parent
    ActionLevelUp *aLevelUp = static_cast<ActionLevelUp*>(
        getParent()->hasAction( "levelUp" )
    );

    if ( aLevelUp )
        if ( mExperience >= 10 && mExperience < 50 && lvl < 1 )
            aLevelUp->doAction();
}

