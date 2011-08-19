#include "state.h"

using namespace Baukasten::Core;

State::State( Entity &parent, const std::string &id ) :
    Object( id ),
    mParent( &parent )
{
}

State::~State()
{
}

const Entity* State::getParent() const
{
    return mParent;
}

