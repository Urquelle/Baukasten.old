#include "form.h"

#include "logical_space.h"
#include "virtual_space.h"

using namespace Baukasten;

Form::Form( const std::string &id ) :
	Drawable( id ),
	ObjectsManager()
{
}

Form::~Form()
{
}

void Form::addLSpace( const std::string &id, LogicalSpace *space )
{
	if ( space && !hasLSpace( id ) )
		mLSpaces[ id ] = space;
}

void Form::removeLSpace( const std::string &id )
{
	if ( hasLSpace( id ) )
		mLSpaces.erase( mLSpaces.find( id ) );
}

void Form::addToLSpace( const std::string &id, Entity *entity )
{
	if ( !entity || !hasLSpace( id ) )
		return;

	LogicalSpace *space = getLSpace( id );

	if ( space )
		space->addEntity( entity );
}

void Form::removeFromLSpace( const std::string &spaceId, const std::string &entityId )
{
	LogicalSpace *space = getLSpace( spaceId );

	if ( !space )
		return;

	if ( space->hasEntity( entityId ) )
		space->removeEntity( entityId );
}

bool Form::hasLSpace( const std::string &id ) const
{
	return ( mLSpaces.find( id ) != mLSpaces.end() );
}

LogicalSpace* Form::getLSpace( const std::string &id ) const
{
	LSpaces::const_iterator it = mLSpaces.find( id );
	return ( it == mLSpaces.end() ) ? 0 : it->second;
}

void Form::addVSpace( const std::string &id, VirtualSpace *space )
{
	if ( space && !hasVSpace( id ) )
		mVSpaces[ id ] = space;
}

void Form::removeVSpace( const std::string &id )
{
	if ( hasVSpace( id ) )
		mVSpaces.erase( mVSpaces.find( id ) );
}

void Form::addToVSpace( const std::string &id, Drawable *entity )
{
	if ( !entity || !hasVSpace( id ) )
		return;

	VirtualSpace *space = getVSpace( id );

	if ( space )
		space->addEntity( entity );
}

void Form::removeFromVSpace( const std::string &spaceId, const std::string &entityId )
{
	VirtualSpace *space = getVSpace( spaceId );

	if ( !space )
		return;

	if ( space->hasEntity( entityId ) )
		space->removeEntity( entityId );
}

bool Form::hasVSpace( const std::string &id ) const
{
	return ( mVSpaces.find( id ) != mVSpaces.end() );
}

VirtualSpace* Form::getVSpace( const std::string &id ) const
{
	VSpaces::const_iterator it = mVSpaces.find( id );
	return ( it == mVSpaces.end() ) ? 0 : it->second;
}

