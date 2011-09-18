#include "virtual_space.h"
#include "drawable.h"

using namespace Baukasten;

VirtualSpace::VirtualSpace() :
	EntityManager()
{
}

VirtualSpace::~VirtualSpace()
{
	// TODO empty mDrawables list and reset the shared_ptr.
}

Drawable*
VirtualSpace::getDrawable( const std::string &id ) const
{
	return static_cast<Drawable*>( EntityManager::getEntity( id ) );
}

void
VirtualSpace::addEntity( Drawable *entity )
{
	add( entity );

	// in order to be able to draw the entities in the
	// order they were added to the collection, it is
	// neccessary to maintain a list of these entities.
	mDrawables.push_back( shared_ptr<Drawable>( entity ) );
}

DrawableList
VirtualSpace::getEntities() const
{
	return mDrawables;
}

