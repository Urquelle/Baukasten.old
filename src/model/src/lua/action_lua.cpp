#include "model/ActionLua"

#include "core/Debug"
#include "model/GameEntity"
#include "model/Bindings"

#include <exception>

using namespace Baukasten;

ActionLua::ActionLua(
		GameEntity &source,
		const std::string &id,
		const std::string &filePath ) :
	Action( source, id ),
	m_filePath( filePath )
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
		s.doFile( m_filePath );
	} catch ( std::exception &e ) {
		BK_DEBUG( e.what() << ": make sure the file " << m_filePath << " is available." );
		BK_ABORT();
	}
}

