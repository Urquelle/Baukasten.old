#include "abstract_space.h"

using namespace Baukasten::Core;

void AbstractSpace::append( const Entity *e )
{
	if ( !e )
		return;

    mEntityList.push_back( e );
}

void AbstractSpace::clear()
{
	mEntityList.erase( mEntityList.begin(), mEntityList.end() );
}

