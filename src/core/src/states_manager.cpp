#include "states_manager.h"

#include "state.h"

using namespace Baukasten;

StatesManager::StatesManager()
{
}

StatesManager::~StatesManager()
{
}

void StatesManager::addState( State *state )
{
	add( state );
}

void StatesManager::addState( const std::string &id, State *state )
{
	add( id, state );
}

State* StatesManager::getState( const std::string &id ) const
{
    return get( id );
}

StateMap StatesManager::getStates() const
{
	return getAll();
}

bool StatesManager::hasState( const std::string &id ) const
{
    return has( id );
}

