#include "virtual_space.h"
#include "drawable.h"

using namespace Baukasten::Core;

VirtualSpace::VirtualSpace( const std::string &id ) :
    AbstractSpace( id )
{
}

VirtualSpace::~VirtualSpace()
{
}

void VirtualSpace::append( const Drawable *o )
{
    AbstractSpace::append( o );
}
