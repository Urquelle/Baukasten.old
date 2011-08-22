#include "form.h"

using namespace Baukasten;

Form::Form( const std::string &id ) :
	Drawable( id )
{
}

Form::~Form()
{
}

void Form::addSpace( const std::string &spaceName, AbstractSpace *space )
{
	if ( space )
		mSpaceMap[ spaceName ] = space;
}
