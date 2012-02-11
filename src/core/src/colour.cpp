#include "core/Colour"

using namespace Baukasten;

Colour::Colour()
{
	Colour( 0, 0, 0, 0 );
}

Colour::Colour( int r, int g, int b, int a ) :
	mR( r ), mG( g ), mB( b ), mA( a )
{
}

Colour::~Colour()
{
}

void
Colour::rgb( int *r, int *g, int *b, int *a ) const
{
	if ( !r || !g || !b )
		return;

	*r = mR;
	*g = mG;
	*b = mB;

	if ( a )
		*a = mA;
}

void
Colour::rgbF( float *r, float *g, float *b, float *a ) const
{
	if ( !r || !g || !b )
		return;

	*r = redF();
	*g = greenF();
	*b = blueF();

	if ( a )
		*a = alphaF();
}

