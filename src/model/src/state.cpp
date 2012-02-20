#include "model/State"

using namespace Baukasten;

State::State( const std::string &id ) :
	Entity( id ),
	m_intState( 0 )
{
}

State::~State()
{
}

State*
State::pack()
{
	State *state = new State( id() );
	state->m_intState = this;
	return state;
}

sigc::signal<void, State*>
State::onChange()
{
	return m_changed;
}

