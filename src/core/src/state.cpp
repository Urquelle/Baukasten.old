#include "state.h"

using namespace Baukasten;

State::State( const std::string &id ) :
    Entity( id ),
	mIsLocked( false )
{
}

State::~State()
{
}

void State::addTo( const GameEntity *entity )
{
	mEntities.push_back( entity );
	mIsLocked = true;
}

