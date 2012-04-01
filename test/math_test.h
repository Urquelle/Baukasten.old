#ifndef MATH_TEST_H_I9AZXHMT
#define MATH_TEST_H_I9AZXHMT

#include "model/Global"
#include "core/Math"

#include <cmath>

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
	CPPUNIT_TEST( testPlusValueVec3 );
	CPPUNIT_TEST( testPlusVecVec3 );
	CPPUNIT_TEST( testMultVecVec3 );
	CPPUNIT_TEST( testMultValueVec3 );
	CPPUNIT_TEST( testMagnitudeVec3 );
	CPPUNIT_TEST( testMagnitudeSqrVec3 );
	CPPUNIT_TEST( testNormVec3 );
	CPPUNIT_TEST( testDotVec3 );
	CPPUNIT_TEST( testCrossVec3 );
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

	void testPlusValueVec3()
	{
		float value = 2.0;
		vec3f v1{ 1.0, 2.0, 3.5 };

		v1 = v1 + value;

		CPPUNIT_ASSERT( v1[BK_X] == 3.0 );
		CPPUNIT_ASSERT( v1[BK_Y] == 4.0 );
		CPPUNIT_ASSERT( v1[BK_Z] == 5.5 );
	}

	void testPlusVecVec3()
	{
		vec3f v1{ 1.0, 2.0, 3.5 };
		vec3f v2{ 2.5, 10.0, 5.7 };

		v1 = v1 + v2;

		f32 eX = 3.5;
		f32 eY = 12.0;
		f32 eZ = 9.2;
		f32 d = 0.00000000000001;

		CPPUNIT_ASSERT( fabs(v1[BK_X] - eX ) < d );
		CPPUNIT_ASSERT( fabs(v1[BK_Y] - eY ) < d );
		CPPUNIT_ASSERT( fabs(v1[BK_Z] - eZ ) < d );
	}

	void testMultVecVec3()
	{
		vec3f v1{ 2.0, 2.0, 3.5 };
		vec3f v2{ 2.5, 10.0, 4.0 };

		v1 = v1 * v2;

		f32 eX =  5.0;
		f32 eY = 20.000000000000001;
		f32 eZ = 14.0;
		f32 d  =  0.00000000000001;

		CPPUNIT_ASSERT( fabs(v1[BK_X] - eX ) < d );
		CPPUNIT_ASSERT( fabs(v1[BK_Y] - eY ) < d );
		CPPUNIT_ASSERT( fabs(v1[BK_Z] - eZ ) < d );
	}

	void testMultValueVec3()
	{
		vec3f v1{ 2.0, 7.0, 3.5 };
		f32 value = 4.0;

		v1 = v1 * value;

		f32 eX =  8.0;
		f32 eY = 28.000000000000001;
		f32 eZ = 14.0;
		f32 d  =  0.00000000000001;

		CPPUNIT_ASSERT( fabs(v1[BK_X] - eX ) < d );
		CPPUNIT_ASSERT( fabs(v1[BK_Y] - eY ) < d );
		CPPUNIT_ASSERT( fabs(v1[BK_Z] - eZ ) < d );
	}

	void testMagnitudeVec3()
	{
		vec3f v1{ 2.0, 7.0, 3.5 };
		f32 e = sqrt( 4.0 + 49.0 + 12.25 ); // sqrt( 65.25 ) == 8.0777472..
		f32 d  =  0.00000000000001;

		CPPUNIT_ASSERT( fabs( v1.mag() - e ) < d );
	}

	void testMagnitudeSqrVec3()
	{
		vec3f v1{ 2.0, 7.0, 3.5 };
		f32 e = 4.0 + 49.0 + 12.25; // 65.25
		f32 d  =  0.00000000000001;

		CPPUNIT_ASSERT( fabs( v1.magSqr() - e ) < d );
	}

	void testNormVec3()
	{
		vec3f v1{ 1.0, 1.0, 1.0 };
		f32 mag = v1.norm().mag();
		f32 ex = 1.0;
		f32 d  =  0.0000001;

		CPPUNIT_ASSERT( fabs( v1.norm().mag() - ex ) <= d );
	}

	void testDotVec3()
	{
		vec3f v1{ 2.0, 3.0, 4.0 };
		f32 e = 4.0 + 9.0 + 16.0;
		f32 d  =  0.00000000000001;

		CPPUNIT_ASSERT( v1.dot( v1 ) == e );
	}

	void testCrossVec3()
	{
		vec3f v1{ 1.0, 1.0, 0.0 };
		vec3f v2{ 1.0, 0.0, 1.0 };
		vec3f v3 = v1.cross( v2 );
		vec3f ex{ 1.0, -1.0, -1.0 };

		CPPUNIT_ASSERT( v3 == ex );
	}

private:
	/* data */
};

#endif /* end of include guard: MATH_TEST_H_I9AZXHMT */

