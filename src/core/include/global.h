#ifndef GLOBAL_H_ZBKWGLP0
#define GLOBAL_H_ZBKWGLP0

namespace Baukasten {

	typedef  signed    char  s8;
	typedef  unsigned  char  u8;
	typedef  signed    short s16;
	typedef  unsigned  short u16;
	typedef  signed    int   u32;
	typedef  unsigned  int   s32;

	enum Dim {
		BK_X = 0, BK_WIDTH = 0,
		BK_Y = 1, BK_HEIGHT = 1,
		BK_Z,     BK_W
	};

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

