#include "game_entity.h"

#include "action.h"
#include "entity_type.h"

using namespace Baukasten::Core;

GameEntity::GameEntity( const std::string &id ) :
	Entity( id )
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::setType( EntityType &type )
{
	mType = &type;
}

EntityType* GameEntity::getType() const
{
	return mType;
}

void GameEntity::setForm( Form &form )
{
    mForm = &form;
}

Form* GameEntity::getForm() const
{
    return mForm;
}

void GameEntity::addEntity( GameEntity &entity )
{
    if ( !hasEntity( entity.getId() ) )
        mEntities[ entity.getId() ] =  &entity;
}

bool GameEntity::hasEntity( const std::string &id ) const
{
    GameEntityMap::const_iterator it = mEntities.find( id );
    return ( it == mEntities.end() );
}

GameEntityMap GameEntity::getEntities() const
{
	return mEntities;
}

void GameEntity::removeEntity( const GameEntity &entity )
{
}

bool GameEntity::hasState( const std::string &id ) const
{
	bool answer = IncStates::hasState( id );
	if ( !answer && getType() )
		answer = getType()->hasState( id );

	return answer;
}

State* GameEntity::getState( const std::string &id ) const
{
	State *state = IncStates::getState( id );

	if ( !state && getType() )
		state = getType()->getState( id );

	return state;
}

