#include "entities.h"
#include "entity_types.h"
#include "actions.h"

#include <lua/action.h>

using namespace Baukasten::Core;

Unit::Unit( const std::string &id ) :
	GameEntity( id ),
	mName( new StateString( "name" ) ),
	mHP( new StateInt( "hp" ) ),
	mMP( new StateInt( "mp" ) ),
	mLevel( new StateInt( "level" ) ),
	mExperience( new StateInt( "experience" ) ),

	mAddExpAction( new AddExperienceAction( *this ) ),
	mLevelUpAction( new LevelUpAction( *this ) ),
	mHitAction( new HitAction( *this ) ),
	mDieAction( new DieAction( *this ) ),
	mLuaAction( new ActionLua( *this, "hello", "scripts/hit_action.lua" ) )
{
	mName->setValue( id );
	mHP->setValue( 40 );
	mMP->setValue( 10 );
	mLevel->setValue( 1 );
	mExperience->setValue( 0 );

	addState( *mName );
	addState( *mHP );
	addState( *mMP );
	addState( *mLevel );
	addState( *mExperience );

	addAction( *mAddExpAction );
	addAction( *mLevelUpAction );
	addAction( *mHitAction );
	addAction( *mDieAction );
	addAction( *mLuaAction );

	setType( *(new BasicClass( "basic" )) );
}

Unit::~Unit()
{
	delete mName;
	delete mHP;
	delete mMP;
	delete mLevel;
	delete mExperience;

	delete mAddExpAction;
	delete mLevelUpAction;
	delete mHitAction;
	delete mLuaAction;
}

std::string Unit::getName() const
{
	return mName->getValue();
}

int Unit::getHP() const
{
	return mHP->getValue();
}

int Unit::getMP() const
{
	return mMP->getValue();
}

int Unit::getLevel() const
{
	return mLevel->getValue();
}

int Unit::getExperience() const
{
	return mExperience->getValue();
}

int Unit::getSex() const
{
	StateInt *state = static_cast<StateInt*>(getState( "sex" ));

	if ( !state )
		return -1;

	return state->getValue();
}

