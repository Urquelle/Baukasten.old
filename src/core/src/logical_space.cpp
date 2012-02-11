#include "core/LogicalSpace"

#include "core/GameEntity"

#include <algorithm>

using namespace Baukasten;

LogicalSpace::LogicalSpace()
{
}

LogicalSpace::~LogicalSpace()
{
}

GameEntity*
LogicalSpace::entity( const string &id ) const
{
	auto it = mMap.find( id );
	if ( it == mMap.end() )
		return 0;

	return it->second;
}

void
LogicalSpace::runActions()
{
	for_each( mList.begin(), mList.end(), []( GameEntity *entity ) {
		entity->runActions();
	});
}

void
LogicalSpace::addEntity( const string &id, GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	BK_ASSERT(
		!hasEntity( id ),
		"id " << id << " must be unique in the collection."
	);

	mMap[ id ] = entity;
	mList.push_back( entity );
}

void
LogicalSpace::addEntity( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	addEntity( entity->id(), entity );
}

list<GameEntity*>
LogicalSpace::entities() const
{
	return mList;
}

bool
LogicalSpace::hasEntity( const string &id ) const
{
	return mMap.count( id );
}

void
LogicalSpace::removeEntity( const string &id )
{
	mMap.erase( mMap.find( id ) );
	mList.remove_if( [&id]( GameEntity *entity ) {
		return entity->id() == id;
	});
}

