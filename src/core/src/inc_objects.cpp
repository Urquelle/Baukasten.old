#include "inc_objects.h"

using namespace Baukasten::Core;

IncObjects::IncObjects()
{
}

IncObjects::~IncObjects()
{
}

void IncObjects::addObject( void *object, const std::string &id )
{
	if ( !hasObject( id ) )
		mObjects[ id ] = object;
}

void* IncObjects::getObject( const std::string &id ) const
{
	ObjectMap::const_iterator it = mObjects.find( id );
	return ( it == mObjects.end() ) ? 0 : it->second;
}

bool IncObjects::hasObject( const std::string &id ) const
{
	return ( mObjects.find( id ) != mObjects.end() );
}

void IncObjects::removeObject( const std::string &id )
{
	mObjects.erase( mObjects.find( id ) );
}

