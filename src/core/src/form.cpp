#include "form.h"

#include "debug.h"
#include "game_entity.h"
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
	BK_ASSERT( entity != 0, "entity must not be 0." );

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
	typedef AbstractManager<Entity> EMap;
	EMap::TMap entities = mVSpace->getEntities();
	EMap::TMap::const_iterator it = entities.begin();
	Form *form = 0;

	while ( it != entities.end() ) {
		form = static_cast<Form*>( it->second.get() );
		if ( form )
			form->render();
		it++;
	}
}

