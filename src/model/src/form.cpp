#include "model/Form"

#include "core/Debug"
#include "model/GameEntity"
#include "model/LogicalSpace"
#include "model/VirtualSpace"

#include <algorithm>

using namespace Baukasten;
using namespace std;

Form::Form( const std::string &id, IGraphics *graphics ) :
	Drawable( id ),
	mLSpace( new LogicalSpace() ),
	mVSpace( new VirtualSpace() ),
	mGraphics( graphics )
{
}

Form::~Form()
{
}

void
Form::addToLSpace( GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	addToLSpace( entity->id(), entity );
}

void
Form::addToLSpace( const string &id, GameEntity *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	mLSpace->addEntity( id, entity );
}

void
Form::removeFromLSpace( const std::string &id )
{
	if ( mLSpace->hasEntity( id ) )
		mLSpace->removeEntity( id );
}

LogicalSpace*
Form::lSpace() const
{
	return mLSpace.get();
}

void
Form::addToVSpace( Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	mVSpace->addEntity( entity );
}

void
Form::addToVSpace( const string &id, Form *entity )
{
	BK_ASSERT( entity != 0, "entity must not be 0." );
	mVSpace->addEntity( id, entity );
}

void
Form::removeFromVSpace( const std::string &id )
{
	if ( mVSpace->hasEntity( id ) )
		mVSpace->removeEntity( id );
}

VirtualSpace*
Form::vSpace() const
{
	return mVSpace.get();
}

void
Form::constructScene()
{
	auto entities = mVSpace->entities();
	for_each( entities.begin(), entities.end(), []( Form* f ) {
		f->constructScene();
		f->render();
	});
}

void
Form::render()
{
}

IGraphics*
Form::graphics() const
{
	return mGraphics;
}

