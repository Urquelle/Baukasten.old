#include "model/EntityType"

#include "model/Debug"

#include <algorithm>

using namespace Baukasten;
using namespace std;

EntityType::EntityType( const std::string &id ) :
	Entity( id ),
	mParent( 0 )
{
}

EntityType::~EntityType()
{
}

void
EntityType::setParent( EntityType *parent )
{
	BK_ASSERT( parent != 0, "parent must not be 0." );

	if ( parent != mParent )
		mParent = parent;
}

EntityType*
EntityType::parent() const
{
	return mParent;
}

void
EntityType::addChild( EntityType *child )
{
	BK_ASSERT( child != 0, "child must not be 0." );

	auto it = find_if( mChildren.begin(), mChildren.end(), [child]( shared_ptr<EntityType> t ) {
		return t.get() == child;
	});

	if ( it == mChildren.end() )
		mChildren.push_back( shared_ptr<EntityType>( child ) );
}

void
EntityType::removeChild( const EntityType *child )
{
	BK_ASSERT( child != 0, "child must not be 0." );

	auto it = find_if( mChildren.begin(), mChildren.end(), [child]( shared_ptr<EntityType> t ) {
		return t.get() == child;
	});

	mChildren.erase( it );
}

State*
EntityType::entityState( const std::string &id )
{
	return 0;
}

