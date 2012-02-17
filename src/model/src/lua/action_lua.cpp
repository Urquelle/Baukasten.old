#include "model/ActionLua"

#include "model/Debug"
#include "model/GameEntity"
#include "model/Bindings"

#include <exception>

using namespace Baukasten;

ActionLua::ActionLua(
		GameEntity &source,
		const std::string &id,
		const std::string &filePath ) :
	Action( source, id ),
	mFilePath( filePath )
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
		s.doFile( mFilePath );
	} catch ( std::exception &e ) {
		BK_DEBUG( e.what() << ": make sure the file " << mFilePath << " is available." );
		BK_ABORT();
	}
}
