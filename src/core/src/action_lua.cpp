#include "action_lua.h"
#include <iostream>

#include <lua.hpp>

using namespace Baukasten::Core;

// register GameEntity Functions here.
static const luaL_Reg bkGEFunctions[] = {
	{}
};

int luaCallback( lua_State *L )
{
	std::cout << "aus lua aufgerufen!" << std::endl;
}

ActionLua::ActionLua(
		GameEntity &source,
		const std::string &id,
		const std::string &filePath ) :
	Action( source, id ),
	mFilePath( filePath )
{
	mLuaState = lua_open();
	luaopen_base( mLuaState );
	lua_register( mLuaState, "doAction", luaCallback );
}

ActionLua::~ActionLua()
{
	lua_close( mLuaState );
}

void ActionLua::doAction( GameEntity *entity )
{
	luaL_dofile( mLuaState, mFilePath.c_str() );
}

