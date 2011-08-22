#include "entity_type.h"

#include <algorithm>

using namespace Baukasten::Core;

EntityType::EntityType( const std::string &id ) :
	Entity( id ),
	mParent( 0 )
{
}

EntityType::~EntityType()
{
}

void EntityType::setParent( EntityType *parent )
{
	if ( !parent )
		return;

	if ( mParent && parent == mParent )
		return;

	mParent = parent;
}

EntityType* EntityType::getParent() const
{
	return mParent;
}

void EntityType::addChild( EntityType *child )
{
	if ( !child )
		return;

	EntityTypeList::iterator it =
		std::find( mChildren.begin(), mChildren.end(), child );

	// the child is already in the list, if the iterator's
	// not equal end().
	if ( it != mChildren.end() )
		return;

	mChildren.push_back( child );
}

void EntityType::removeChild( const EntityType *child )
{
	if ( !child )
		return;

	mChildren.erase(
		std::find( mChildren.begin(), mChildren.end(), child )
	);
}

State* EntityType::getState( const std::string &id ) const
{
	State *state = StatesManager::getState( id );

	if ( !state && mParent )
		state = mParent->getState( id );

	return state;
}

State* EntityType::getEntityState( const std::string &id )
{
	return 0;
}

