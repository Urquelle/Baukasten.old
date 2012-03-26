#include "model/EntityType"

#include "core/Debug"

#include <algorithm>

using namespace Baukasten;
using namespace std;

EntityType::EntityType( const string &id ) :
	Entity( id ),
	m_parent( 0 )
{
}

EntityType::~EntityType()
{
}

void
EntityType::setParent( EntityType *parent )
{
	BK_ASSERT( parent != 0, "parent must not be 0." );

	if ( parent != m_parent )
		m_parent = parent;
}

EntityType*
EntityType::parent() const
{
	return m_parent;
}

void
EntityType::addChild( EntityType *child )
{
	BK_ASSERT( child != 0, "child must not be 0." );

	auto it = find_if( m_children.begin(), m_children.end(), [child]( shared_ptr<EntityType> t ) {
		return t.get() == child;
	});

	if ( it == m_children.end() )
		m_children.push_back( shared_ptr<EntityType>( child ) );
}

void
EntityType::removeChild( const EntityType *child )
{
	BK_ASSERT( child != 0, "child must not be 0." );

	auto it = find_if( m_children.begin(), m_children.end(), [child]( shared_ptr<EntityType> t ) {
		return t.get() == child;
	});

	m_children.erase( it );
}

State*
EntityType::entityState( const string &id )
{
	return 0;
}

