#include <lua/action.h>
#include <game_entity.h>
#include <lua/global.h>

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
	SLB::Script s;
	s.doString("SLB.using(SLB)");
	s.set("entity", entity);
	s.set("action", this);
	s.doFile( mFilePath );
}

