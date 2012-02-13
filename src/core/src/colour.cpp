#include "core/Colour"

#include "model/Debug"

using namespace Baukasten;
#define BK_RGB(r, g, b) \
    ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff))
#define BK_RGBA( r, g, b, a ) \
	((a << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff))

static const uint bk_colors[] = {
	BK_RGB(   0,   0,   0 ), // black
	BK_RGB( 255, 255, 255 ), // white
	BK_RGB( 255,   0,   0 ), // red
	BK_RGB(   0, 255,   0 ), // green
	BK_RGB(   0,   0, 255 ), // blue
	BK_RGB( 128, 128, 128 )  // gray
};

Colour::Colour() :
	mColor( bk_colors[BK_BLACK] )
{
}

Colour::Colour( uint r, uint g, uint b, uint a ) :
	mColor( BK_RGBA( r, g, b, a ) )
{
}

Colour::Colour( const Colour &other )
{
	if ( this == &other )
		return;

	mColor = other.value();
}

Colour::Colour( Colour const *other )
{
	if ( this == other )
		return;

	mColor = other->value();
}

Colour::Colour( const Colours value ) :
	mColor( bk_colors[value] )
{
}

Colour::~Colour()
{
}

uint
Colour::red() const
{
	return ( mColor >> 16 ) & 0xff;
}

uint
Colour::green() const
{
	return ( mColor >> 8 ) & 0xff;
}

uint
Colour::blue() const
{
	return ( mColor ) & 0xff;
}

uint
Colour::alpha() const
{
	return ( mColor >> 24 ) & 0xff;
}

uint
Colour::value() const
{
	return mColor;
}

void
Colour::rgb( uint *r, uint *g, uint *b, uint *a ) const
{
	if ( !r || !g || !b )
		return;

	*r = ( mColor >> 16 ) & 0xff;
	*g = ( mColor >> 8 ) & 0xff;
	*b = ( mColor ) & 0xff;

	if ( a )
		*a = ( mColor >> 24 ) & 0xff;
}

float
Colour::redF() const
{
	return red() / 255.0;
}

float
Colour::greenF() const
{
	return green() / 255.0;
}

float
Colour::blueF() const
{
	return blue() / 255.0;
}

float
Colour::alphaF() const
{
	return alpha() / 255.0;
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

Colour&
Colour::operator=( const Colour &other )
{
	if ( this == &other )
		return *this;

	mColor = other.value();
	return *this;
}

bool
Colour::operator==( const Colour &other ) const
{
	if ( this == &other )
		return true;

	return (
		mColor	== other.value()
	);
}

bool
Colour::operator==( const Colours &colour ) const
{
	return mColor == bk_colors[colour];
}

bool
Colour::operator!=( const Colour &other ) const
{
	if ( this == &other )
		return false;

	return !operator==( other );

}

bool
Colour::operator!=( const Colours &colour ) const
{
	return !operator==( colour );

}

