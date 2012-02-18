#include "core/Color"

#include "core/Debug"

using namespace Baukasten;

static const u32 bk_colors[] = {
	BK_RGB(   0,   0,   0 ), // black
	BK_RGB( 255, 255, 255 ), // white
	BK_RGB( 255,   0,   0 ), // red
	BK_RGB(   0, 255,   0 ), // green
	BK_RGB(   0,   0, 255 ), // blue
	BK_RGB( 128, 128, 128 )  // gray
};

Color::Color() :
	mColor( bk_colors[BK_BLACK] )
{
}

Color::Color( u32 r, u32 g, u32 b, u32 a ) :
	mColor( BK_RGBA( r, g, b, a ) )
{
}

Color::Color( const Color &other )
{
	if ( this == &other )
		return;

	mColor = other.value();
}

Color::Color( Color const *other )
{
	if ( this == other )
		return;

	mColor = other->value();
}

Color::Color( const Colors value )
{
	int size = sizeof( bk_colors ) / sizeof( u32 );
	mColor = ( value >= size ) ?
		bk_colors[BK_BLACK] :
		bk_colors[value];
}

Color::~Color()
{
}

u32
Color::red() const
{
	return ( mColor >> 16 ) & 0xff;
}

u32
Color::green() const
{
	return ( mColor >> 8 ) & 0xff;
}

u32
Color::blue() const
{
	return ( mColor ) & 0xff;
}

u32
Color::alpha() const
{
	return ( mColor >> 24 ) & 0xff;
}

u32
Color::value() const
{
	return mColor;
}

void
Color::rgb( u32 *r, u32 *g, u32 *b, u32 *a ) const
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
Color::redF() const
{
	return red() / 255.0;
}

float
Color::greenF() const
{
	return green() / 255.0;
}

float
Color::blueF() const
{
	return blue() / 255.0;
}

float
Color::alphaF() const
{
	return alpha() / 255.0;
}

void
Color::rgbF( float *r, float *g, float *b, float *a ) const
{
	if ( !r || !g || !b )
		return;

	*r = redF();
	*g = greenF();
	*b = blueF();

	if ( a )
		*a = alphaF();
}

Color&
Color::operator=( const Color &other )
{
	if ( this == &other )
		return *this;

	mColor = other.value();
	return *this;
}

bool
Color::operator==( const Color &other ) const
{
	if ( this == &other )
		return true;

	return (
		mColor	== other.value()
	);
}

bool
Color::operator==( const Colors &color ) const
{
	return mColor == bk_colors[color];
}

bool
Color::operator!=( const Color &other ) const
{
	if ( this == &other )
		return false;

	return !operator==( other );

}

bool
Color::operator!=( const Colors &color ) const
{
	return !operator==( color );

}

