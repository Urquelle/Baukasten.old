#include "unit.h"
#include "basic_type.h"

#include <lua/action.h>

#include <OGRE/Ogre.h>

using namespace Baukasten;

Unit::Unit( const std::string &id ) :
	GameEntity( id )
{
	addAction( new ActionLua( *this, "addExperience", "scripts/add_exp.lua" ) );
	addAction( new ActionLua( *this, "levelUp", "scripts/level_up.lua" ) );
	addAction( new ActionLua( *this, "die", "scripts/die.lua" ) );
	addAction( new ActionLua( *this, "hit", "scripts/hit.lua" ) );

	setType( new BasicType( "basic" ) );

	setName( id );
}

Unit::~Unit()
{
	if ( EntityType *type = getType() )
		delete type;
}

std::string Unit::getName() const
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

int Unit::getHP() const
{
	if ( hasState( "hp" ) )
		return getState<StateInt*>( "hp" )->getValue();
	return 0;
}

int Unit::getMP() const
{
	if ( hasState( "mp" ) )
		return getState<StateInt*>( "mp" )->getValue();
	return 0;
}

int Unit::getLevel() const
{
	if ( hasState( "level" ) )
		return getState<StateInt*>( "level" )->getValue();
	return 0;
}

int Unit::getExperience() const
{
	if ( hasState( "exp" ) )
		return getState<StateInt*>( "exp" )->getValue();
	return 0;
}

int Unit::getSex() const
{
	return 0;
}

