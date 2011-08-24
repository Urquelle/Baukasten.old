#include "objects_manager.h"

using namespace Baukasten;

ObjectsManager::ObjectsManager()
{
}

ObjectsManager::~ObjectsManager()
{
}

void ObjectsManager::addObject( const std::string &id, void *object )
{
	if ( !hasObject( id ) )
		mObjects[ id ] = object;
}

bool ObjectsManager::hasObject( const std::string &id ) const
{
	return ( mObjects.find( id ) != mObjects.end() );
}

void ObjectsManager::removeObject( const std::string &id )
{
	mObjects.erase( mObjects.find( id ) );
}

