#ifndef DEBUG_QEAOHFVH
#define DEBUG_QEAOHFVH

#ifndef NDEBUG
#	include <iostream>
#	define BK_DEBUG( X ) std::cout << __FILE__ << " " << __LINE__ << ": " << X << std::endl;
#else
#	define BK_DEBUG( X )
#endif

#endif /* end of include guard: DEBUG_QEAOHFVH */
