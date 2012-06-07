#include "model/include/model_interface.h"

#include "model/GameEntity"

using namespace Baukasten;

ModelInterface* ModelInterface::m_instance = 0;

ModelInterface&
ModelInterface::instance()
{
	if ( !m_instance ) {
		m_instance = new ModelInterface();
	}

	return *m_instance;
}

// ModelInterfacePrivate {{{
namespace Baukasten {

struct ElementNode {
	GameEntity* entity;
	ElementNode* parent;
	list<ElementNode*> children;
	static u32         count;
	u32 id;

	ElementNode() :
		entity( 0 )
	{
	}

	ElementNode( const string &id, u32 uniqueId ) :
		entity( new GameEntity( id ) ),
		id( uniqueId )
	{
		entity->m_node = this;
		++count;
	}

	~ElementNode()
	{
		--count;
		if ( entity != 0 ) {
			delete entity;
			entity = 0;
		}

		for( ElementNode *element : children ) {
			if ( element )
				delete element;
		}

		children.clear();
	}

	void clear()
	{
		if ( entity != 0 ) {
			delete entity;
			entity = 0;
		}

		ElementNode *element = 0;
		for ( auto i = children.begin(); i != children.end(); ++i) {
			element = *i;
			if ( element )
				delete element;
		}

		children.clear();
	}

	void destroyEntity( GameEntity *entity )
	{
		BK_ASSERT( entity->m_node != this, "can't destroy myself!" );

		entity->m_node->parent->children.remove( entity->m_node );
		delete entity->m_node;
	}

	u32 uniqueId( const GameEntity *entity ) const
	{
		return entity->m_node->id;
	}

	ElementNode*
	node( GameEntity *entity )
	{
		return entity->m_node;
	}

	u32
	elementCount() const
	{
		return count;
	}
};

u32 ElementNode::count = 0;

class ModelInterfacePrivate {
public:

	ModelInterfacePrivate() :
		m_idPool( 0 ),
		m_root( new ElementNode() )
	{
		m_root->entity = 0;
	}

	~ModelInterfacePrivate()
	{
		delete m_root;
	}

	void
	shutdown()
	{
		m_root->clear();
	}

	GameEntity*
	createEntity( const string &id, GameEntity *parent )
	{
		ElementNode *node = 0;
		if ( !parent ) {
			BK_ASSERT( m_root->children.size() == 0,
				"root element already created! provide a parent object to create a child element."
			);

			node = m_root;
		} else {
			node = m_root->node( parent );
		}

		u32 uniqueId = ++m_idPool;
		ElementNode *element = new ElementNode( id, uniqueId );
		node->children.push_back( element );
		element->parent = node;

		m_entityMap[ uniqueId ] = element->entity;

		return element->entity;
	}

	void
	destroyEntity( const u32 id )
	{
		BK_ASSERT( m_entityMap.count( id ) == 1, "id must be present in the collection!" );
		GameEntity *entity = m_entityMap[ id ];
		destroyEntity( entity );
	}

	void
	destroyEntity( GameEntity *entity )
	{
		m_root->destroyEntity( entity );
	}

	u32
	uniqueId( const GameEntity *entity ) const
	{
		return m_root->uniqueId( entity );
	}

	GameEntity*
	entity( const u32 id )
	{
		if ( m_entityMap.count( id ) == 0 )
			return 0;
		return m_entityMap[ id ];
	}

	u32
	entityCount() const
	{
		return m_root->count;
	}

private:
	map<u32, GameEntity*>  m_entityMap;
	u32                    m_idPool;
	ElementNode*           m_root;
};
} /* Baukasten  */
// }}}

ModelInterface::ModelInterface() :
	m_impl( new ModelInterfacePrivate() )
{
}

ModelInterface::~ModelInterface()
{
	if ( m_impl ) {
		delete m_impl;
		m_impl = 0;
	}
}

void
ModelInterface::shutdown()
{
	m_impl->shutdown();
}

GameEntity*
ModelInterface::createEntity( const string &id, GameEntity *parent )
{
	return m_impl->createEntity( id, parent );
}

void
ModelInterface::destroyEntity( const u32 id )
{
	m_impl->destroyEntity( id );
}

void
ModelInterface::destroyEntity( GameEntity *entity )
{
	m_impl->destroyEntity( entity );
}

u32
ModelInterface::uniqueId( const GameEntity *entity ) const
{
	return m_impl->uniqueId( entity );
}

GameEntity*
ModelInterface::entity( const u32 id )
{
	return m_impl->entity( id );
}

u32
ModelInterface::entityCount() const
{
	return m_impl->entityCount();
}

