#include "abstract_space.h"

using namespace Eisenfaust::Core;

void AbstractSpace::append( const Entity *e )
{
    if ( !e )
        return;

    mEntityList.push_back( e );
}

void AbstractSpace::clear()
{
    mEntityList.clear();
}

