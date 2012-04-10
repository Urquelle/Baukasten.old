#include "model/GameEntity"

#include "core/Debug"
#include "model/Action"
#include "model/ActionManager"
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

GameEntity::GameEntity( const string &id ) :
	Entity( id ),
	m_actions( new ActionManager() ),
	m_node( 0 ),
	m_parent( 0 ),
	m_states( new StateManager() ),
	m_type( 0 )
{
}

GameEntity::GameEntity( const GameEntity &rhs ) :
	Entity( rhs.id() ),
	m_actions( new ActionManager() ),
	m_form( rhs.form() ),
	m_node( 0 ),
	m_parent( rhs.parent() ),
	m_states( new StateManager() ),
	m_type( rhs.type() )
{
}

GameEntity::~GameEntity()
{
}

void
GameEntity::setType( EntityType *type )
{
	if ( type )
		m_type = type;
}

void
GameEntity::addType( EntityType *type )
{
	if ( !type || type == m_type ) return;
	if ( !m_type ) {
		m_type = type;
	} else {
		type->setParent( m_type );
		m_type = type;
	}

}

EntityType*
GameEntity::type() const
{
	return m_type;
}

void
GameEntity::setForm( Form *form )
{
	BK_ASSERT( form != 0, "form must not be 0." );
	m_form = shared_ptr<Form>( form );
}

Form*
GameEntity::form() const
{
	return m_form.get();
}

void
GameEntity::addState( const string &id, State *state )
{
	BK_ASSERT( state != 0, "state must not be 0." );

	state->onChange().connect(
		sigc::mem_fun( this, &GameEntity::stateChanged )
	);

	m_states->addState( id, state );
}

void
GameEntity::addState( State *state )
{
	if ( state )
		addState( state->id(), state );
}

bool
GameEntity::hasState( const string &id ) const
{
	bool answer = m_states->hasState( id );
	if ( !answer && type() )
		answer = type()->hasState( id );

	return answer;
}

void
GameEntity::addChild( GameEntity *child )
{
	if ( child )
		addChild( child->id(), child );
}

void
GameEntity::addChild( const string &id, GameEntity *child )
{
	BK_ASSERT( this != child, "you can't have a GameEntity be its own child." );
	BK_ASSERT(
		!isAncestor( this, child ),
		"you can't assign a parent GameEntity to be its own grandchild."
	);

	if ( m_children.find( id ) == m_children.end() ) {
		m_children[ id ] = child;
		child->setParent( this );
	}
}

GameEntity*
GameEntity::child( const string &id ) const
{
	auto it = m_children.find( id );
	return ( it == m_children.end() ) ? 0 : it->second;
}

GameEntityMap
GameEntity::children() const
{
	return m_children;
}

void
GameEntity::removeChild( const string &id )
{
	m_children.erase( m_children.find( id ) );
}

void
GameEntity::setParent( GameEntity *parent )
{
	BK_ASSERT( parent != 0, "parent must not be 0." );
	BK_ASSERT( parent != this, "GameEntity object can't be its own parent." );

	m_parent = parent;
}

GameEntity*
GameEntity::parent() const
{
	return m_parent;
}

Action*
GameEntity::action( const string &id ) const
{
	return m_actions->action( id );
}

map<string, shared_ptr<Action> >
GameEntity::actions() const
{
	return m_actions->actions();
}

list<Action*>
GameEntity::invokedActions() const
{
	return m_actions->invokedActions();
}

void
GameEntity::addAction( Action *action )
{
	m_actions->addAction( action );
}

void
GameEntity::addAction( const string &id, Action *action )
{
	m_actions->addAction( id, action );
}

bool
GameEntity::hasAction( const string &id ) const
{
	return m_actions->hasAction( id );
}

void
GameEntity::dropAction( const string &id )
{
	m_actions->dropAction( id );
}

void
GameEntity::invokeAction( const string &id )
{
	m_actions->invokeAction( id );
}

void
GameEntity::invokeAction( const string &id, GameEntity *target )
{
	m_actions->invokeAction( id, target );
}

void
GameEntity::invokeAction( const string &id, list<GameEntity*> targets )
{
	m_actions->invokeAction( id, targets );
}

void
GameEntity::runActions()
{
	// run own actions first
	auto al = m_actions->invokedActions();
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
	return m_stateChanged;
}

ActionSignal&
GameEntity::onActionInvoked()
{
	return m_actionInvoked;
}

ActionSignal&
GameEntity::onActionRun()
{
	return m_actionRun;
}

void
GameEntity::stateChanged( State *state )
{
	m_stateChanged.emit( this, state );
}

