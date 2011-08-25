#include "entities.h"
#include "entity_types.h"
#include "actions/actions.h"

#include <lua/action.h>

#include <OGRE/Ogre.h>

using namespace Baukasten;

Unit::Unit( const std::string &id ) :
	GameEntity( id )
{
	addAction( new AddExperienceAction( *this ) );
	addAction( new LevelUpAction( *this ) );
	addAction( new DieAction( *this ) );
	addAction( new ActionLua( *this, "hit", "scripts/hit_action.lua" ) );

	setType( new BasicClass( "basic" ) );

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

