#ifndef DEBUG_QEAOHFVH
#define DEBUG_QEAOHFVH

#ifndef NDEBUG

#include <iostream>

#define BK_DEBUG( X ) std::cout << __FILE__ << " " << __LINE__ \
	<< ": " << X << std::endl;
#define BK_PRINT( X ) std::cout << X << std::endl;
#define BK_ERROR( X ) { std::cerr << __FILE__ << " " << __LINE__ \
	<< ": " << X << std::endl; abort(); }
#else

#define BK_DEBUG( X )
#define BK_PRINT( X )
#define BK_ERROR( X )

#endif

#endif /* end of include guard: DEBUG_QEAOHFVH */
