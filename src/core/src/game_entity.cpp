#include "game_entity.h"

#include "action.h"
#include "debug.h"
#include "form.h"
#include "logical_space.h"

#include <algorithm>

using namespace Baukasten;
using namespace std;

bool
isAncestor( GameEntity *entity, GameEntity *child )
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
	mParent( 0 )
{
}

GameEntity::GameEntity( const GameEntity &rhs ) :
	Entity( rhs.getId() ),
	mType( rhs.getType() ),
	mParent( rhs.getParent() ),
	mForm( rhs.getForm() )
{
}

GameEntity::~GameEntity()
{
}

void
GameEntity::setType( EntityType *type )
{
	if ( type )
		mType = type;
}

EntityType*
GameEntity::getType() const
{
	return mType;
}

void
GameEntity::setForm( Form *form )
{
	BK_ASSERT( form != 0, "form must not be 0." );
	mForm = shared_ptr<Form>( form );
}

Form*
GameEntity::getForm() const
{
	return mForm.get();
}

void
GameEntity::addState( const std::string &id, State *state )
{
	BK_ASSERT( state != 0, "state must not be 0." );

	state->onChange().connect(
		sigc::mem_fun( this, &GameEntity::stateChanged )
	);

	StateManager::addState( id, state );
}

void
GameEntity::addState( State *state )
{
	if ( state )
		addState( state->getId(), state );
}

bool
GameEntity::hasState( const std::string &id ) const
{
	bool answer = StateManager::hasState( id );
	if ( !answer && getType() )
		answer = getType()->hasState( id );

	return answer;
}

void
GameEntity::addChild( GameEntity *child )
{
	BK_ASSERT( this != child, "you can't have a GameEntity be its own child." );
	BK_ASSERT(
		!isAncestor( this, child ),
		"you can't assign a parent GameEntity to be its own grandchild."
	);

	if ( mChildren.find( child->getId() ) == mChildren.end() ) {
		mChildren[ child->getId() ] = shared_ptr<GameEntity>( child );
		child->setParent( this );
	}
}

GameEntity*
GameEntity::getChild( const std::string &id ) const
{
	auto it = mChildren.find( id );
	return ( it == mChildren.end() ) ? 0 : it->second.get();
}

void
GameEntity::removeChild( const std::string &id )
{
	mChildren.erase( mChildren.find( id ) );
}

void
GameEntity::setParent( GameEntity *parent )
{
	BK_ASSERT( parent != 0, "parent must not be 0." );
	BK_ASSERT( parent != this, "GameEntity object can't be its own parent." );

	mParent = parent;
}

GameEntity*
GameEntity::getParent() const
{
	return mParent;
}

void
GameEntity::runActions()
{
	// run own actions first
	auto al = getInvokedActions();
	for_each( al.begin(), al.end(), []( Action *a ) {
		a->run();
	});

	// run children's actions
	Form *form = getForm();
	if ( form )
		getForm()->getLSpace()->runActions();
}

StateSignal&
GameEntity::onStateChanged()
{
	return mStateChanged;
}

ActionSignal&
GameEntity::onActionInvoked()
{
	return mActionInvoked;
}

ActionSignal&
GameEntity::onActionRun()
{
	return mActionRun;
}

void
GameEntity::stateChanged( State *state )
{
	mStateChanged.emit( this, state );
}

