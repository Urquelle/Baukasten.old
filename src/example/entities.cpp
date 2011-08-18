#include "entities.h"
#include "actions.h"

Unit::Unit( const std::string &id ) :
	Entity( id ),
	mName( new GenericState<std::string>( *this, "name" ) ),
	mHP( new GenericState<int>( *this, "hp" ) ),
	mMP( new GenericState<int>( *this, "mp" ) ),
	mLevel( new GenericState<int>( *this, "level" ) ),
	mExperience( new GenericState<int>( *this, "experience" ) ),

	mAddExpAction( new AddExperienceAction( *this ) ),
	mLevelUpAction( new LevelUpAction( *this ) ),
	mHitAction( new HitAction( *this ) ),
	mDieAction( new DieAction( *this ) )
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

