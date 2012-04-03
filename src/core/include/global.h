#ifndef GLOBAL_H_ZBKWGLP0
#define GLOBAL_H_ZBKWGLP0

/*!
 * \file core/include/global.h
 *
 * \brief global include file for Core module.
 *
 * this file contains all the basic declarations that
 * are used across the core module.
 */

/*! \defgroup core Core */
/*! \defgroup math Mathimatics */

#include <string>

namespace Baukasten {
	using namespace std;

	typedef signed   char  s8;
	typedef unsigned char  u8;
	typedef signed   short s16;
	typedef unsigned short u16;
	typedef signed   int   u32;
	typedef unsigned int   s32;
	typedef float          f32;

	enum Dim {
		BK_X = 0, BK_WIDTH = 0,
		BK_Y = 1, BK_HEIGHT = 1,
		BK_Z,     BK_W
	};

}

/*!
 * \brief swap 2 byte integer.
 *
 * swaps LSB <-> MSB of a 2 byte integer.
 *
 * \param value 16 bit / 2 byte integer value to be swapped.
 */
inline Baukasten::u16
_bk_swap_u16( Baukasten::u16 value )
{
	return ( ( ( value & 0x00FF ) << 8 ) | ( ( value & 0xFF00 >> 8 ) ) );
}

/*!
 * \brief swap 4 byte integer.
 *
 * swaps the order of bytes of a 4 byte integer.
 *
 * \param value 32 bit / 4 byte integer value to be swapped.
 */
inline Baukasten::u32
_bk_swap_u32( Baukasten::u32 value )
{
	return (
		( ( value & 0x000000FF ) << 24 ) | ( ( value & 0x0000FF00 << 8 ) ) |
		( ( value & 0xFF000000 ) >> 24 ) | ( ( value & 0x00FF0000 >> 8 ) )
	);
}

union _bk_u32f32 {
	Baukasten::u32 m_asu32;
	Baukasten::f32 m_asf32;
};

/*!
 * \brief swap 4 byte float.
 *
 * swaps the order of bytes of a 4 byte float.
 *
 * \param value 32 bit / 4 byte  float value to be swapped.
 */
inline Baukasten::f32
_bk_swap_f32( Baukasten::f32 value )
{
	_bk_u32f32 v;
	v.m_asf32 = value;
	v.m_asu32 = _bk_swap_u32( v.m_asu32 );
	return v.m_asu32;
}

#define BK_RGB(r, g, b) \
    ((0xff << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff))
#define BK_RGBA( r, g, b, a ) \
	((a << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff))

#define BK_PIMPL_PTR( Class ) \
	friend class Class##Private; \
	Class##Private* m_impl

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#ifdef __GNUC__
#	define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#	define DEPRECATED(func) __declspec(deprecated) func
#else
#	pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#	define DEPRECATED(func) func
#endif

#endif /* end of include guard: GLOBAL_H_ZBKWGLP0 */

