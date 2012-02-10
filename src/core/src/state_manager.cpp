#include "core/StateManager"

#include "core/State"
#include "core/Debug"

using namespace Baukasten;

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void
StateManager::addState( State *state )
{
	BK_ASSERT( state != 0, "state must not be 0." );
	add( state );
}

void
StateManager::addState( const std::string &id, State *state )
{
	BK_ASSERT( state != 0, "state must not be 0." );
	add( id, state );
}

StateManager::TMap
StateManager::getStates() const
{
	return getAll();
}

bool
StateManager::hasState( const std::string &id ) const
{
	return has( id );
}

