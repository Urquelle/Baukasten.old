#include "virtual_space.h"
#include "drawable.h"

using namespace Baukasten;

VirtualSpace::VirtualSpace( const std::string &id ) :
    LogicalSpace( id )
{
}

VirtualSpace::~VirtualSpace()
{
}

void VirtualSpace::append( const Drawable *o )
{
    LogicalSpace::append( o );
}
