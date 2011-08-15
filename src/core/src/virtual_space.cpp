#include "virtual_space.h"
#include "renderable_entity.h"

using namespace Baukasten::Core;

VirtualSpace::VirtualSpace()
{
}

VirtualSpace::~VirtualSpace()
{
}

void VirtualSpace::append( const RenderableEntity &ro )
{
    AbstractSpace::append( ro );
}
