#include "form.h"

#include "logical_space.h"
#include "virtual_space.h"

using namespace Baukasten;

Form::Form( const std::string &id ) :
	Drawable( id ),
	ObjectManager(),
	mLSpace( new LogicalSpace() ),
	mVSpace( new VirtualSpace() )
{
}

Form::~Form()
{
	delete mLSpace;
	delete mVSpace;
}

void Form::addToLSpace( Entity *entity )
{
	if ( !entity )
		return;

	mLSpace->addEntity( entity );
}

void Form::removeFromLSpace( const std::string &id )
{
	if ( mLSpace->hasEntity( id ) )
		mLSpace->removeEntity( id );
}

LogicalSpace* Form::getLSpace() const
{
	return mLSpace;
}

void Form::addToVSpace( Drawable *entity )
{
	if ( !entity )
		return;

	mVSpace->addEntity( entity );
}

void Form::removeFromVSpace( const std::string &id )
{
	if ( mVSpace->hasEntity( id ) )
		mVSpace->removeEntity( id );
}

VirtualSpace* Form::getVSpace() const
{
	return mVSpace;
}

