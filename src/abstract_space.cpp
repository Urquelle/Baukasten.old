#include "abstract_space.h"

using namespace Eisenfaust;

void AbstractSpace::append( const Entity *e )
{
    m_entityList.push_back( e );
}

void AbstractSpace::clear()
{
    m_entityList.clear();
}

