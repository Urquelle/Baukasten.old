#include "abstract_space.h"

using namespace Eisenfaust;

void AbstractSpace::append( const Object *o )
{
    m_entityList.push_back( o );
}

void AbstractSpace::clear()
{
    m_entityList.clear();
}

