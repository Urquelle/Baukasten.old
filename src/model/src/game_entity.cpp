#include "model/GameEntity"

#include "model/Action"
#include "model/Debug"
#include "model/Form"
#include "model/LogicalSpace"

#include <algorithm>

using namespace Baukasten;
using namespace std;

bool
isAncestor( GameEntity *entity, GameEntity *child )
{
	while ( GameEntity *parent = entity->parent() ) {
		if ( parent == child )
			return true;
		parent = parent->parent();
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
	Entity( rhs.id() ),
	mType( rhs.type() ),
	mForm( rhs.form() ),
	mParent( rhs.parent() )
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
GameEntity::type() const
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
GameEntity::form() const
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
		addState( state->id(), state );
}

bool
GameEntity::hasState( const std::string &id ) const
{
	bool answer = StateManager::hasState( id );
	if ( !answer && type() )
		answer = type()->hasState( id );

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

	if ( mChildren.find( child->id() ) == mChildren.end() ) {
		mChildren[ child->id() ] = shared_ptr<GameEntity>( child );
		child->setParent( this );
	}
}

GameEntity*
GameEntity::child( const std::string &id ) const
{
	auto it = mChildren.find( id );
	return ( it == mChildren.end() ) ? 0 : it->second.get();
}

GameEntityMap
GameEntity::children() const
{
	return mChildren;
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
GameEntity::parent() const
{
	return mParent;
}

void
GameEntity::runActions()
{
	// run own actions first
	auto al = invokedActions();
	for_each( al.begin(), al.end(), []( Action *a ) {
		a->run();
	});

	// run children's actions
	Form *_form = form();
	if ( _form )
		_form->lSpace()->runActions();
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

