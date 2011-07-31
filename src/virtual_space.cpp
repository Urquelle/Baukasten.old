#include "virtual_space.h"
#include "renderable_object.h"

using namespace Eisenfaust;

VirtualSpace::VirtualSpace()
{
}

VirtualSpace::~VirtualSpace()
{
}

void VirtualSpace::append( const RenderableObject *ro )
{
    AbstractSpace::append( ro );
}
