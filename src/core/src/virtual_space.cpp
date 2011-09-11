#include "virtual_space.h"
#include "drawable.h"

using namespace Baukasten;

VirtualSpace::VirtualSpace() :
	LogicalSpace()
{
}

VirtualSpace::~VirtualSpace()
{
}

Drawable* VirtualSpace::getDrawable( const std::string &id ) const
{
	return static_cast<Drawable*>( LogicalSpace::getEntity( id ) );
}

