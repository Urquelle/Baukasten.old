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

void GameEntity::addAction( Action &action )
{
    if ( !hasAction( action.getId() ) )
        mActions[ action.getId() ] =  &action;
}

Action* GameEntity::getAction( const std::string &id ) const
{
    ActionMap::const_iterator it = mActions.find( id );
    return ( it == mActions.end() ) ? 0 : it->second;
}

ActionMap GameEntity::getActions() const
{
	return mActions;
}

bool GameEntity::hasAction( const std::string &id ) const
{
    ActionMap::const_iterator it = mActions.find( id );
    return ( it != mActions.end() );
}

void GameEntity::invokeAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        mActionQueue.push_back( action );
    }
}

void GameEntity::invokeAction( const std::string &id, GameEntity &target )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTarget( target );
        mActionQueue.push_back( action );
    }
}

void GameEntity::invokeAction( const std::string &id, GameEntityList targets )
{
    Action *action = getAction( id );

    if ( action && !action->isActive() ) {
        action->clear();
        action->setActive( true );
        action->setTargets( targets );
        mActionQueue.push_back( action );
    }
}

void GameEntity::dropAction( const std::string &id )
{
    Action *action = getAction( id );

    if ( action && action->isActive() ) {
		action->setActive( false );
        ActionList::iterator it = mActionQueue.begin();

        while ( it != mActionQueue.end() ) {
            if ( *it == action ) {
                mActionQueue.erase( it );
                break;
            }
			it++;
        }
    }
}

void GameEntity::runActions()
{
    ActionList::const_iterator it = mActionQueue.begin();
    while ( it != mActionQueue.end() )
        (*it++)->run();
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
	bool answer = Entity::hasState( id );
	if ( !answer )
		answer = getType()->hasState( id );

	return answer;
}

State* GameEntity::getState( const std::string &id ) const
{
	State *state = Entity::getState( id );

	if ( !state )
		state = getType()->getState( id );

	return state;
}

