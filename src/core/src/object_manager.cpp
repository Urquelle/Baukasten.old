#include "object_manager.h"

#include "debug.h"

using namespace Baukasten;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::addObject( const std::string &id, void *object )
{
	BK_ASSERT( object != 0, "object must not be 0." );

	if ( !hasObject( id ) )
		mObjects[ id ] = object;
}

bool ObjectManager::hasObject( const std::string &id ) const
{
	return ( mObjects.find( id ) != mObjects.end() );
}

void ObjectManager::removeObject( const std::string &id )
{
	mObjects.erase( mObjects.find( id ) );
}

