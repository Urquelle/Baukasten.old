#include "core/State"

using namespace Baukasten;

State::State( const std::string &id ) :
	Entity( id ),
	mIntState( 0 )
{
}

State::~State()
{
}

State*
State::pack()
{
	State *state = new State( id() );
	state->mIntState = this;
	return state;
}

sigc::signal<void, State*>
State::onChange()
{
	return mChanged;
}

