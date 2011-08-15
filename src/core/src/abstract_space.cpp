#include "abstract_space.h"

using namespace Baukasten::Core;

void AbstractSpace::append( const Entity &e )
{
    mEntityList.push_back( &e );
}

void AbstractSpace::clear()
{
    mEntityList.clear();
}

