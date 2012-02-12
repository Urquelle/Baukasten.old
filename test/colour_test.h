#ifndef COLOUR_TEST_H_KIEQYUWU
#define COLOUR_TEST_H_KIEQYUWU

#include "core/Colour"
#include "model/Debug"
#include "model/Global"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Baukasten;
using namespace CppUnit;

class ColourTest : public TestFixture {
	CPPUNIT_TEST_SUITE( ColourTest );
	CPPUNIT_TEST( testInit );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
	}

	void tearDown()
	{
	}

	void testInit()
	{
        Colour c;
        CPPUNIT_ASSERT_EQUAL( 0, c.red() );
	}
};
#endif /* end of include guard: COLOUR_TEST_H_KIEQYUWU */

