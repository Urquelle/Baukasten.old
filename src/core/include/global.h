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

#define BK_PIMPL_PTR( Class ) \
	friend class Class##Private; \
	Class##Private* mImpl

#if defined(EXPORT_LIB)
#   define BAUKASTEN_EXPORT __attribute__((visibility("default")))
#else
#   define BAUKASTEN_EXPORT
#endif

#endif /* end of include guard: GLOBAL_H_ZBKWGLP0 */

