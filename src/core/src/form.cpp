#include "form.h"

using namespace Baukasten::Core;

Form::Form( const std::string &id ) :
	Drawable( id )
{
}

Form::~Form()
{
}

void Form::addSpace( const std::string &spaceName, AbstractSpace &space )
{
	mSpaceMap[ spaceName ] = &space;
}
