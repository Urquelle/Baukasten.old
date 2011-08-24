#include "state_manager.h"

#include "state.h"

using namespace Baukasten;

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::addState( State *state )
{
	add( state );
}

void StateManager::addState( const std::string &id, State *state )
{
	add( id, state );
}

StateMap StateManager::getStates() const
{
	return getAll();
}

bool StateManager::hasState( const std::string &id ) const
{
    return has( id );
}

