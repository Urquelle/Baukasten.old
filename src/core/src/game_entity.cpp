#include "game_entity.h"

#include "action.h"
#include "entity_type.h"

using namespace Baukasten;

GameEntity::GameEntity( const std::string &id ) :
	Entity( id )
{
}

GameEntity::~GameEntity()
{
}

void GameEntity::setType( EntityType *type )
{
	if ( type )
		mType = type;
}

EntityType* GameEntity::getType() const
{
	return mType;
}

void GameEntity::setForm( Form *form )
{
	if ( form )
		mForm = form;
}

Form* GameEntity::getForm() const
{
    return mForm;
}

bool GameEntity::hasState( const std::string &id ) const
{
	bool answer = StatesManager::hasState( id );
	if ( !answer && getType() )
		answer = getType()->hasState( id );

	return answer;
}

State* GameEntity::getState( const std::string &id ) const
{
	State *state = StatesManager::getState( id );

	if ( !state && getType() )
		state = getType()->getState( id );

	return state;
}

