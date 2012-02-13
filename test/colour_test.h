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
    CPPUNIT_TEST( testCopyCtor );
    CPPUNIT_TEST( testColoursCtor );
    CPPUNIT_TEST( testOpAssign );
    CPPUNIT_TEST( testOpEqual );
    CPPUNIT_TEST( testOpEqualInt );
    CPPUNIT_TEST( testOpNotEqual );
    CPPUNIT_TEST( testOpNotEqualInt );
    CPPUNIT_TEST( testOutOfIndex );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
        c1 = new Colour();
        c2 = new Colour( 125, 125, 125, 255 );
	}

	void tearDown()
	{
        if ( c1 == c2 ) {
            delete c1;
            c1 = c2 = 0;
        }

        if ( c1 ) {
            delete c1;
            c1 = 0;
        }

        if ( c2 ) {
            delete c2;
            c2 = 0;
        }
	}

	void testInit()
	{
        uint r = 0, g = 0, b = 0, a = 255;

        CPPUNIT_ASSERT_EQUAL( r, c1->red() );
        CPPUNIT_ASSERT_EQUAL( g, c1->green() );
        CPPUNIT_ASSERT_EQUAL( b, c1->blue() );
        CPPUNIT_ASSERT_EQUAL( a, c1->alpha() );
	}

    void testCopyCtor()
    {
        Colour c3 = c2;
        uint r = 125, g = 125, b = 125, a = 255;

        CPPUNIT_ASSERT_EQUAL( r, c3.red() );
        CPPUNIT_ASSERT_EQUAL( g, c3.green() );
        CPPUNIT_ASSERT_EQUAL( b, c3.blue() );
        CPPUNIT_ASSERT_EQUAL( a, c3.alpha() );
    }

    void testColoursCtor()
    {
        Colour c3( Colour::BK_WHITE );

        uint r = 255, g = 255, b = 255, a = 255;

        CPPUNIT_ASSERT_EQUAL( r, c3.red() );
        CPPUNIT_ASSERT_EQUAL( g, c3.green() );
        CPPUNIT_ASSERT_EQUAL( b, c3.blue() );
        CPPUNIT_ASSERT_EQUAL( a, c3.alpha() );
    }

    void testOpAssign()
    {
        Colour c3;
        Colour c4( 0, 125, 255, 255 );

        c3 = c4;

        uint r = 0, g = 125, b = 255, a = 255;

        CPPUNIT_ASSERT_EQUAL( r, c3.red() );
        CPPUNIT_ASSERT_EQUAL( g, c3.green() );
        CPPUNIT_ASSERT_EQUAL( b, c3.blue() );
        CPPUNIT_ASSERT_EQUAL( a, c3.alpha() );
    }

    void testOpEqual()
    {
        Colour c3( 125, 255, 125, 255 );
        Colour c4( 125, 255, 125, 255 );

        CPPUNIT_ASSERT_EQUAL( true, c3 == c4 );
    }

    void testOpEqualInt()
    {
        Colour c3( 255, 255, 255, 255 );
        CPPUNIT_ASSERT_EQUAL( true, c3 == Colour::BK_WHITE );
    }

    void testOpNotEqual()
    {
        Colour c3( 125, 255, 125, 255 );
        Colour c4( 124, 255, 125, 255 );

        CPPUNIT_ASSERT_EQUAL( true, c3 != c4 );
    }

    void testOpNotEqualInt()
    {
        Colour c3( 0, 0, 255, 255 );
        CPPUNIT_ASSERT_EQUAL( true, c3 == Colour::BK_BLUE );
    }

    void testOutOfIndex()
    {
        int BK_FANTASY_COLOR = 9999;

        Colour c3( (Colour::Colours) BK_FANTASY_COLOR );
        uint r = 0, g = 0, b = 0, a = 255;

        CPPUNIT_ASSERT_EQUAL( r, c3.red() );
        CPPUNIT_ASSERT_EQUAL( g, c3.green() );
        CPPUNIT_ASSERT_EQUAL( b, c3.blue() );
        CPPUNIT_ASSERT_EQUAL( a, c3.alpha() );
    }

private:
    Colour *c1;
    Colour *c2;
};
#endif /* end of include guard: COLOUR_TEST_H_KIEQYUWU */

