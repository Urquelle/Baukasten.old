#include "logical_space.h"

#include "game_entity.h"

#include <algorithm>

using namespace Baukasten;

LogicalSpace::LogicalSpace()
{
}

LogicalSpace::~LogicalSpace()
{
}

void
LogicalSpace::runActions()
{
	for_each( mList.begin(), mList.end(), []( GameEntity *entity ) {
		entity->runActions();
	});
}

void
LogicalSpace::addEntity( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	BK_ASSERT(
		!hasEntity( entity->getId() ),
		"id " << entity->getId() << " must be unique in the collection."
	);

	mMap[ entity->getId() ] = entity;
	mList.push_back( entity );
}

bool
LogicalSpace::hasEntity( const string &id ) const
{
	return ( mMap.find( id ) != mMap.end() );
}

void
LogicalSpace::removeEntity( const string &id )
{
	mMap.erase( mMap.find( id ) );
}

