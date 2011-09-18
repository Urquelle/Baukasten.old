#include "form.h"

#include "debug.h"
#include "game_entity.h"
#include "logical_space.h"
#include "virtual_space.h"

#include <algorithm>

using namespace Baukasten;
using namespace std;

Form::Form( const std::string &id ) :
	Drawable( id ),
	mLSpace( new LogicalSpace() ),
	mVSpace( new VirtualSpace() )
{
}

Form::~Form()
{
	delete mLSpace;
	delete mVSpace;
}

void Form::addToLSpace( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	mLSpace->addGameEntity( entity );
}

void Form::removeFromLSpace( const std::string &id )
{
	if ( mLSpace->hasGameEntity( id ) )
		mLSpace->removeGameEntity( id );
}

LogicalSpace* Form::getLSpace() const
{
	return mLSpace;
}

void Form::addToVSpace( Drawable *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
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

void Form::render()
{
	auto entities = mVSpace->getEntities();
	for_each( entities.begin(), entities.end(), []( shared_ptr<Drawable> d ) {
		d->render();
	});
}

