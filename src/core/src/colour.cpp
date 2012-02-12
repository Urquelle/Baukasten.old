#include "core/Colour"

#include "model/Debug"

using namespace Baukasten;

Colour::Colour() :
	mR(0), mG(0), mB(0), mA(255)
{
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

