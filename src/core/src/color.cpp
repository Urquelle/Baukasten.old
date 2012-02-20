#include "core/Color"

#include "core/Debug"

using namespace Baukasten;

static const u32 _bk_colors[] = {
	BK_RGB(   0,   0,   0 ), // black
	BK_RGB( 255, 255, 255 ), // white
	BK_RGB( 255,   0,   0 ), // red
	BK_RGB(   0, 255,   0 ), // green
	BK_RGB(   0,   0, 255 ), // blue
	BK_RGB( 128, 128, 128 )  // gray
};

Color::Color() :
	m_color( _bk_colors[BK_BLACK] )
{
}

Color::Color( u32 r, u32 g, u32 b, u32 a ) :
	m_color( BK_RGBA( r, g, b, a ) )
{
}

Color::Color( const Color &other )
{
	if ( this == &other )
		return;

	m_color = other.value();
}

Color::Color( Color const *other )
{
	if ( this == other )
		return;

	m_color = other->value();
}

Color::Color( const Colors value )
{
	int size = sizeof( _bk_colors ) / sizeof( u32 );
	m_color = ( value >= size ) ?
		_bk_colors[BK_BLACK] :
		_bk_colors[value];
}

Color::~Color()
{
}

u32
Color::red() const
{
	return ( m_color >> 16 ) & 0xff;
}

u32
Color::green() const
{
	return ( m_color >> 8 ) & 0xff;
}

u32
Color::blue() const
{
	return ( m_color ) & 0xff;
}

u32
Color::alpha() const
{
	return ( m_color >> 24 ) & 0xff;
}

u32
Color::value() const
{
	return m_color;
}

void
Color::rgb( u32 *r, u32 *g, u32 *b, u32 *a ) const
{
	if ( !r || !g || !b )
		return;

	*r = ( m_color >> 16 ) & 0xff;
	*g = ( m_color >> 8 ) & 0xff;
	*b = ( m_color ) & 0xff;

	if ( a )
		*a = ( m_color >> 24 ) & 0xff;
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

	m_color = other.value();
	return *this;
}

bool
Color::operator==( const Color &other ) const
{
	if ( this == &other )
		return true;

	return (
		m_color	== other.value()
	);
}

bool
Color::operator==( const Colors &color ) const
{
	return m_color == _bk_colors[color];
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

