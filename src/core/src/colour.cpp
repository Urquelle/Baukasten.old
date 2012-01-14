#include "colour.h"

using namespace Baukasten;

Colour::Colour()
{
	Colour( 0, 0, 0, 0 );
}

Colour::Colour( int r, int g, int b, int alpha ) :
	mR( r ), mG( g ), mB( b ), mAlpha( alpha )
{
}

Colour::~Colour()
{
}

