#include "unit.h"

#include <lua/action_lua.h>

#include <OGRE/Ogre.h>

using namespace Baukasten;

Unit::Unit( const std::string &id ) :
	GameEntity( id )
{
	addAction( new ActionLua( *this, "addExperience", "scripts/add_exp.lua" ) );
	addAction( new ActionLua( *this, "levelUp", "scripts/level_up.lua" ) );
	addAction( new ActionLua( *this, "die", "scripts/die.lua" ) );
	addAction( new ActionLua( *this, "hit", "scripts/hit.lua" ) );
}

Unit::~Unit()
{
}

std::string Unit::getName()
{
	if ( hasState( "name" ) )
		return getState<StateString*>( "name" )->getValue();
	return "";
}

void Unit::setName( const std::string &name )
{
	if ( hasState( "name" ) )
		getState<StateString*>( "name" )->setValue( getId() );
}

int Unit::getHP()
{
	if ( hasState( "hp" ) )
		return getState<StateInt*>( "hp" )->getValue();
	return 0;
}

int Unit::getMP()
{
	if ( hasState( "mp" ) )
		return getState<StateInt*>( "mp" )->getValue();
	return 0;
}

int Unit::getLevel()
{
	if ( hasState( "level" ) )
		return getState<StateInt*>( "level" )->getValue();
	return 0;
}

int Unit::getExperience()
{
	if ( hasState( "exp" ) )
		return getState<StateInt*>( "exp" )->getValue();
	return 0;
}

int Unit::getSex()
{
	return 0;
}

