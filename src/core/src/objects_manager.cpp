#include "objects_manager.h"

using namespace Baukasten::Core;

ObjectsManager::ObjectsManager()
{
}

ObjectsManager::~ObjectsManager()
{
}

void ObjectsManager::addObject( void *object, const std::string &id )
{
	if ( !hasObject( id ) )
		mObjects[ id ] = object;
}

void* ObjectsManager::getObject( const std::string &id ) const
{
	ObjectMap::const_iterator it = mObjects.find( id );
	return ( it == mObjects.end() ) ? 0 : it->second;
}

bool ObjectsManager::hasObject( const std::string &id ) const
{
	return ( mObjects.find( id ) != mObjects.end() );
}

void ObjectsManager::removeObject( const std::string &id )
{
	mObjects.erase( mObjects.find( id ) );
}

