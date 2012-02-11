#include "model/VirtualSpace"

#include "model/Debug"
#include "model/Form"

using namespace Baukasten;

VirtualSpace::VirtualSpace()
{
}

VirtualSpace::~VirtualSpace()
{
}

Form*
VirtualSpace::entity( const std::string &id ) const
{
	auto it = mMap.find( id );
	if ( it == mMap.end() )
		return 0;

	return it->second;
}

void
VirtualSpace::addEntity( const string &id, Form *entity )
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
VirtualSpace::addEntity( Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	BK_ASSERT(
		!hasEntity( entity->id() ),
		"id " << entity->id() << " must be unique in the collection."
	);

	addEntity( entity->id(), entity );
}

list<Form*>
VirtualSpace::entities() const
{
	return mList;
}

bool
VirtualSpace::hasEntity( const string &id ) const
{
	return mMap.count( id );
}

void
VirtualSpace::removeEntity( const string &id )
{
	mMap.erase( mMap.find( id ) );
	mList.remove_if( [&id]( Form *form ) {
		return form->id() == id;
	});
}

