#include "action.h"

using namespace Baukasten::Core;

Action::Action( Entity &source, const std::string &id ) :
    Entity( id ),
    mSource( &source ),
    mActive( false )
{
}

Action::~Action()
{
}

const Entity* Action::getSource() const
{
    return mSource;
}

void Action::clear()
{
    mTarget = 0;
    mTargetList.erase( mTargetList.begin(), mTargetList.end() );
}

bool Action::isActive() const
{
    return mActive;
}

void Action::setTarget( Entity &target )
{
    mTarget = &target;
}

Entity* Action::getTarget()
{
    return mTarget;
}

void Action::setTarget( EntityList &targetList )
{
    mTargetList = targetList;
}

