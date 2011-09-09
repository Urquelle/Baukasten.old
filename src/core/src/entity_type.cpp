#include "entity_type.h"

#include "debug.h"

#include <algorithm>

using namespace Baukasten;

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
	BK_ASSERT( parent != 0, "parent must not be 0." );

	if ( parent != mParent )
		mParent = parent;
}

EntityType* EntityType::getParent() const
{
	return mParent;
}

void EntityType::addChild( EntityType *child )
{
	BK_ASSERT( child != 0, "child must not be 0." );

	EntityTypeList::iterator it =
		std::find( mChildren.begin(), mChildren.end(), child );

	if ( it == mChildren.end() )
		mChildren.push_back( child );
}

void EntityType::removeChild( const EntityType *child )
{
	BK_ASSERT( child != 0, "child must not be 0." );

	mChildren.erase(
		std::find( mChildren.begin(), mChildren.end(), child )
	);
}

State* EntityType::getEntityState( const std::string &id )
{
	return 0;
}

