#include "inc_states.h"

#include "state.h"

using namespace Baukasten::Core;

IncStates::IncStates()
{
}

IncStates::~IncStates()
{
}

void IncStates::addState( State &state )
{
    if ( !hasState( state.getId() ) )
        mStates[ state.getId() ] = &state;
}

State* IncStates::getState( const std::string &id ) const
{
    StateMap::const_iterator it = mStates.find( id );
    return ( it == mStates.end() ) ? 0 : it->second;
}

StateMap IncStates::getStates() const
{
	return mStates;
}

bool IncStates::hasState( const std::string &id ) const
{
    StateMap::const_iterator it = mStates.find( id );
    return ( it != mStates.end() );
}

