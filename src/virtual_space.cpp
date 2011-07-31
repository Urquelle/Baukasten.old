#include "virtual_space.h"
#include "renderable_entity.h"

using namespace Eisenfaust;

VirtualSpace::VirtualSpace()
{
}

VirtualSpace::~VirtualSpace()
{
}

void VirtualSpace::append( const RenderableEntity *ro )
{
    AbstractSpace::append( ro );
}
