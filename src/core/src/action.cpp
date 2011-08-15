#include "action.h"

using namespace Baukasten::Core;

Action::Action( Entity &parent ) :
    Entity(),
    mParent( &parent )
{
}

Action::Action( Entity &parent, const std::string &id ) :
    Entity( id ),
    mParent( &parent )
{
}

Action::~Action()
{
}

const Entity* Action::getParent() const
{
    return mParent;
}

void Action::doAction( Entity &target )
{
    Entity *tParent = mParent;
    mParent = &target;
    doAction();
    mParent = tParent;
}

void Action::doAction( std::list<Entity*> targetList )
{
    std::list<Entity*>::const_iterator it = targetList.begin();
    while ( it != targetList.end() ) {
        doAction( *(static_cast<Entity*>(*it)) );
    }
}

