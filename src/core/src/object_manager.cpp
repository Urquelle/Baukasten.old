#include "object_manager.h"

using namespace Baukasten;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::addObject( const std::string &id, void *object )
{
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

