#ifndef MATH_TEST_H_I9AZXHMT
#define MATH_TEST_H_I9AZXHMT

#include "model/Global"
#include "core/Math"

using namespace Baukasten;
using namespace CppUnit;

class MathTest : public TestFixture {
	CPPUNIT_TEST_SUITE( MathTest );
	CPPUNIT_TEST( testInitVec2 );
	CPPUNIT_TEST( testCopyConstructorVec2 );
	CPPUNIT_TEST( testAdditionVec2 );
	CPPUNIT_TEST( testEqualVec2 );
	CPPUNIT_TEST( testNotEqualVec2 );
	CPPUNIT_TEST( testInitVec3 );
	CPPUNIT_TEST( testCopyConstructorVec3 );
	CPPUNIT_TEST( testAdditionVec3 );
	CPPUNIT_TEST( testEqualVec3 );
	CPPUNIT_TEST( testNotEqualVec3 );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
	}

	void tearDown()
	{
	}

	void testInitVec2()
	{
		vec2<float> v( 1.0, 2.0 );

		float expectedX = 1.0;
		float expectedY = 2.0;

		CPPUNIT_ASSERT_EQUAL( expectedX, v[BK_X] );
		CPPUNIT_ASSERT_EQUAL( expectedY, v[BK_Y] );
	}

	void testCopyConstructorVec2()
	{
		vec2<int> v1( 5, 10 );
		vec2<int> v2 = v1;

		int eX = 5;
		int eY = 10;

		CPPUNIT_ASSERT_EQUAL( eX, v2[BK_X] );
		CPPUNIT_ASSERT_EQUAL( eY, v2[BK_Y] );
	}

	void testAdditionVec2()
	{
		vec2<float> v1( 2.0, 4.0 );
		vec2<float> v2( 3.0, 6.0 );
		vec2<float> v3 = v1 + v2;

		float eX = 5.0;
		float eY = 10.0;

		CPPUNIT_ASSERT_EQUAL( eX, v3[BK_X] );
		CPPUNIT_ASSERT_EQUAL( eY, v3[BK_Y] );
	}

	void testEqualVec2()
	{
		vec2<float> v1( 3.0, 6.0 );
		vec2<float> v2( 3.0, 6.0 );

		CPPUNIT_ASSERT( v1 == v2 );
	}

	void testNotEqualVec2()
	{
		vec2<float> v1( 3.0, 6.0 );
		vec2<float> v2( 3.0, 5.0 );

		CPPUNIT_ASSERT( v1 != v2 );
	}

	void testInitVec3()
	{
		vec3<float> v( 1.0, 2.0, 3.0 );

		float eX = 1.0;
		float eY = 2.0;
		float eZ = 3.0;

		CPPUNIT_ASSERT_EQUAL( eX, v[BK_X] );
		CPPUNIT_ASSERT_EQUAL( eY, v[BK_Y] );
		CPPUNIT_ASSERT_EQUAL( eZ, v[BK_Z] );
	}

	void testCopyConstructorVec3()
	{
		vec3<int> v1( 5, 10, 15 );
		vec3<int> v2 = v1;

		int eX = 5;
		int eY = 10;
		int eZ = 15;

		CPPUNIT_ASSERT_EQUAL( eX, v2[BK_X] );
		CPPUNIT_ASSERT_EQUAL( eY, v2[BK_Y] );
		CPPUNIT_ASSERT_EQUAL( eZ, v2[BK_Z] );
	}

	void testAdditionVec3()
	{
		vec3<float> v1( 2.0, 4.0, 6.0 );
		vec3<float> v2( 3.0, 6.0, 9.0 );
		vec3<float> v3 = v1 + v2;

		float eX = 5.0;
		float eY = 10.0;
		float eZ = 15.0;

		CPPUNIT_ASSERT_EQUAL( eX, v3[BK_X] );
		CPPUNIT_ASSERT_EQUAL( eY, v3[BK_Y] );
		CPPUNIT_ASSERT_EQUAL( eZ, v3[BK_Z] );
	}

	void testEqualVec3()
	{
		vec3<float> v1( 3.0, 6.0, 9.0 );
		vec3<float> v2( 3.0, 6.0, 9.0 );

		CPPUNIT_ASSERT( v1 == v2 );
	}

	void testNotEqualVec3()
	{
		vec3<float> v1( 3.0, 6.0, 0.0 );
		vec3<float> v2( 3.0, 5.0, 0.0 );

		CPPUNIT_ASSERT( v1 != v2 );
	}

private:
	/* data */
};

#endif /* end of include guard: MATH_TEST_H_I9AZXHMT */

