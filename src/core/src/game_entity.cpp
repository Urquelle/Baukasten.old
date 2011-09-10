#include "game_entity.h"

#include "action.h"
#include "debug.h"

using namespace Baukasten;
using namespace std;

bool isAncestor( GameEntity *entity, GameEntity *child )
{
	while ( GameEntity *parent = entity->getParent() ) {
		if ( parent == child )
			return true;
		parent = parent->getParent();
	}
	return false;
}

// --------- GameEntity ---------------- //

GameEntity::GameEntity( const std::string &id ) :
	Entity( id ),
	mType( 0 ),
	mForm( 0 ),
	mParent( 0 )
{
}

GameEntity::~GameEntity()
{
	BK_DEBUG( getId() << ": selfdestrict in 1 ... 2 ... 3!" );

	// destroy children
	GameEntityMap::iterator it = mChildren.begin();
	while ( it != mChildren.end() ) {
		delete it->second;
		it++;
	}
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

void GameEntity::addState( const std::string &id, State *state )
{
	BK_ASSERT( state != 0, "state must not be 0." );

	state->onChange().connect(
		sigc::mem_fun( this, &GameEntity::stateChanged )
	);

	StateManager::addState( id, state );
}

void GameEntity::addState( State *state )
{
	if ( state )
		addState( state->getId(), state );
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
	BK_ASSERT( this != child, "you can't have a GameEntity be its own child." );
	BK_ASSERT(
		!isAncestor( this, child ),
		"you can't assign a parent GameEntity to be its own grandchild."
	);

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
	BK_ASSERT( parent != 0, "parent must not be 0." );
	BK_ASSERT( parent != this, "GameEntity object can't be its own parent." );

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
	GameEntityMap::const_iterator cit = mChildren.begin();
	while ( cit != mChildren.end() ) {
		cit->second->runActions();
		cit++;
	}
}

sigc::signal<void, GameEntity*, State*> GameEntity::onStateChanged()
{
	return mStateChanged;
}

sigc::signal<void, GameEntity*, Action*> GameEntity::onActionInvoked()
{
	return mActionInvoked;
}

sigc::signal<void, GameEntity*, Action*> GameEntity::onActionRun()
{
	return mActionRun;
}

void GameEntity::stateChanged( State *state )
{
	mStateChanged.emit( this, state );
}

