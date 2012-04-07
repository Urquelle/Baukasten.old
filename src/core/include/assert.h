#ifndef ASSERT_H_BTACVQZG
#define ASSERT_H_BTACVQZGASSERT_H_BTACVQZG

#if ASSERTIONS_ENABLED

#include <iostream>

#define BK_ABORT() asm( "int3" )
#define BK_ASSERT( TST, MSG ) \
	if ( TST ) { \
	} else { \
		std::cerr << __FILE__ << ": " << __LINE__ << "\n" \
		<< #TST << " failed!" << "\n" << MSG << std::endl; \
		BK_ABORT(); \
	}

#else
#define BK_ABORT()
#define BK_ASSERT( TST, MSG ) ( (void)0 )
#endif
#endif /* end of include guard: ASSERT_H_BTACVQZGASSERT_H_BTACVQZG */

