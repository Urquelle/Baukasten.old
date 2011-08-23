#include "game_entity.h"

#include "action.h"

using namespace Baukasten;

GameEntity::GameEntity( const std::string &id ) :
	Entity( id ),
	mType( 0 ),
	mForm( 0 )
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

