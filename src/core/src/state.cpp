#include "state.h"

using namespace Baukasten;

State::State( const std::string &id ) :
    Entity( id ),
	mIntState( 0 )
{
}

State::~State()
{
}

State* State::pack()
{
	State *state = new State( getId() );
	state->mIntState = this;
	return state;
}

