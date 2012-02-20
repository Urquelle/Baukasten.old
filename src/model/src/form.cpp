#include "model/Form"

#include "core/Debug"
#include "model/GameEntity"
#include "model/LogicalSpace"
#include "model/VirtualSpace"

#include <algorithm>

using namespace Baukasten;
using namespace std;

Form::Form( const std::string &id, IGraphics *graphics ) :
	Drawable( id ),
	m_lSpace( new LogicalSpace() ),
	m_vSpace( new VirtualSpace() ),
	m_graphics( graphics )
{
}

Form::~Form()
{
}

void
Form::addToLSpace( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	addToLSpace( entity->id(), entity );
}

void
Form::addToLSpace( const string &id, GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	m_lSpace->addEntity( id, entity );
}

void
Form::removeFromLSpace( const std::string &id )
{
	if ( m_lSpace->hasEntity( id ) )
		m_lSpace->removeEntity( id );
}

LogicalSpace*
Form::lSpace() const
{
	return m_lSpace.get();
}

void
Form::addToVSpace( Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	m_vSpace->addEntity( entity );
}

void
Form::addToVSpace( const string &id, Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	m_vSpace->addEntity( id, entity );
}

void
Form::removeFromVSpace( const std::string &id )
{
	if ( m_vSpace->hasEntity( id ) )
		m_vSpace->removeEntity( id );
}

VirtualSpace*
Form::vSpace() const
{
	return m_vSpace.get();
}

void
Form::constructScene()
{
	auto entities = m_vSpace->entities();
	for_each( entities.begin(), entities.end(), []( Form* f ) {
		f->constructScene();
		f->render();
	});
}

void
Form::render()
{
}

IGraphics*
Form::graphics() const
{
	return m_graphics;
}

