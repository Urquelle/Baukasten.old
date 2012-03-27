#include "model/ActionLua"

#include "core/Debug"
#include "model/GameEntity"
#include "model/Bindings"

#include <exception>

using namespace Baukasten;

ActionLua::ActionLua(
		GameEntity &source,
		const string &id,
		const string &path ) :
	Action( source, id ),
	m_path( path )
{
	wrapClasses();
}

ActionLua::~ActionLua()
{
}

void ActionLua::doAction( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );

	SLB::Script s;
	s.doString( "SLB.using(SLB)" );
	s.set( "entity", entity );
	s.set( "action", this );
	s.set( "source", source() );

	try {
		s.doFile( m_path );
	} catch ( exception &e ) {
		BK_DEBUG( e.what() << ": make sure the file " << m_path << " is available." );
		BK_ABORT();
	}
}

