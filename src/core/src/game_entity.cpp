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
	bool answer = StateManager::hasState( id );
	if ( !answer && getType() )
		answer = getType()->hasState( id );

	return answer;
}

void GameEntity::addChild( GameEntity *child )
{
	if ( mChildren.find( child->getId() ) == mChildren.end() )
		mChildren[ child->getId() ] = child;
}

GameEntity* GameEntity::getChild( const std::string &id ) const
{
	GameEntityMap::const_iterator it = mChildren.find( id );
	return ( it == mChildren.end() ) ? 0 : it->second;
}

void GameEntity::removeChild( const std::string &id )
{
	mChildren.erase( mChildren.find( id ) );
}

void GameEntity::setParent( GameEntity *parent )
{
	mParent = parent;
}

GameEntity* GameEntity::getParent() const
{
	return mParent;
}

void GameEntity::runActions()
{
	// run own actions first
	ActionList al = getInvokedActions();
	ActionList::const_iterator it = al.begin();
	while ( it != al.end() ) {
		(*it)->run();
		it++;
	}

	// run children's actions
	GameEntity *e = 0;
	GameEntityMap::const_iterator cit = mChildren.begin();
	while ( cit != mChildren.end() ) {
		al = cit->second->getInvokedActions();
		it = al.begin();

		while ( it != al.end() ) {
			(*it)->run();
			it++;
		}

		cit++;
	}
}

