#ifndef DEBUG_QEAOHFVH
#define DEBUG_QEAOHFVH

#ifndef NDEBUG

#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

#define BK_DEBUG( X ) cout << __FILE__ << " " << __LINE__ << ": " << X << endl;
#define BK_ASSERT( TST, MSG )							\
		( (TST) ? (void)0								\
			: (cerr << __FILE__ "(" << __LINE__			\
				<< "): Assertion failed " #TST			\
				<< " " << MSG << endl,abort()))
#else

#define BK_DEBUG( X )
#define BK_ASSERT( TST, MSG ) ( (void)0 )

#endif

#endif /* end of include guard: DEBUG_QEAOHFVH */
