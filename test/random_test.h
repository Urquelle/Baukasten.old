#ifndef RANDOM_TEST_H_1OE53RFT
#define RANDOM_TEST_H_1OE53RFT

#include "math/Random"

#include "core/Debug"

using namespace Baukasten;
using namespace CppUnit;

/*!
 * \brief RandomTest class declaration.
 */
class RandomTest : public TestFixture {
	CPPUNIT_TEST_SUITE( RandomTest );
	CPPUNIT_TEST( testRandom );
	CPPUNIT_TEST_SUITE_END();
public:
	void testRandom()
	{
		f32 r = Random::random();
		f32 r2 = Random::random();

		CPPUNIT_ASSERT( r != r2 );
	}

private:
	/* data */
};

#endif /* end of include guard: RANDOM_TEST_H_1OE53RFT */

