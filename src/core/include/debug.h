#ifndef DEBUG_QEAOHFVH
#define DEBUG_QEAOHFVH

#ifndef NDEBUG

#include <iostream>
#include <assert.h>

#define BK_DEBUG( X ) std::cout << __FILE__ << " " << __LINE__ << ": " << X << std::endl;
#define BK_ASSERT( TST, MSG )							\
		( (TST) ? (void)0								\
			: (std::cerr << __FILE__ "(" << __LINE__	\
				<< "): Assertion failed " #TST			\
				<< " " << MSG << std::endl,abort()))

#else

#define BK_DEBUG( X )
#define BK_ASSERT( TST, MSG ) ( (void)0 )

#endif

#endif /* end of include guard: DEBUG_QEAOHFVH */
