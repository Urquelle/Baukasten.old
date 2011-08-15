#include "generic_state.h"

using namespace Baukasten::Core;

template<class T>
GenericState<T>::GenericState( Entity &parent ) :
	State( parent )
{
}

template<class T>
GenericState<T>::GenericState( Entity &parent, const std::string &id ) :
	State( parent, id )
{
}

template<class T>
const T GenericState<T>::getValue() const
{
    return mValue;
}

template<class T>
void GenericState<T>::setValue( const T &value )
{
    mValue = value;
}

