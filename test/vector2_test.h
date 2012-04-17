#ifndef VECTOR2_TEST_H_8EFWUNPO
#define VECTOR2_TEST_H_8EFWUNPO

#include "math/Vector2"

#include <cmath>

using namespace Baukasten;
using namespace CppUnit;

/*!
 * \break Vector2Test class declaration.
 */
class Vector2Test : public TestFixture {
	CPPUNIT_TEST_SUITE( Vector2Test );
	CPPUNIT_TEST( testInit );
	CPPUNIT_TEST( testCopyConstructor );
	CPPUNIT_TEST( testAssign );
	CPPUNIT_TEST( testAdditionVec2 );
	CPPUNIT_TEST( testAdditionScalar );
	CPPUNIT_TEST( testMultVec2 );
	CPPUNIT_TEST( testMultScalar );
	CPPUNIT_TEST( testEqual );
	CPPUNIT_TEST( testNotEqual );
	CPPUNIT_TEST( testDivVec2 );
	CPPUNIT_TEST( testDivScalar );
	CPPUNIT_TEST( testMag );
	CPPUNIT_TEST( testMagSqr );
	CPPUNIT_TEST( testNormalised );
	CPPUNIT_TEST( testNormalise );
	CPPUNIT_TEST( testDot );
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
		Vector2 v( 1.0, 2.0 );

		f32 expectedX = 1.0;
		f32 expectedY = 2.0;

		CPPUNIT_ASSERT_EQUAL( expectedX, static_cast<f32>( v[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( expectedY, static_cast<f32>( v[BK_Y] ) );
	}

	void testCopyConstructor()
	{
		Vector2 v1( 5, 10 );
		Vector2 v2 = v1;

		f32 eX = 5;
		f32 eY = 10;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v2[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v2[BK_Y] ) );
	}

	void testAssign()
	{
		Vector2 v;

		v[BK_X] = 5.0;
		v[BK_Y] = 7.0;

		f32 eX = 5.0;
		f32 eY = 7.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v[BK_Y] ) );
	}

	void testAdditionVec2()
	{
		Vector2 v1( 2.0, 4.0 );
		Vector2 v2( 3.0, 6.0 );
		Vector2 v3 = v1 + v2;

		f32 eX = 5.0;
		f32 eY = 10.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
	}

	void testAdditionScalar()
	{
		Vector2 v1( 2.0, 4.0 );
		f32 scalar = 1.5;

		Vector2 v2( v1 + scalar );

		f32 eX = 3.5;
		f32 eY = 5.5;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v2[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v2[BK_Y] ) );
	}

	void testMultVec2()
	{
		Vector2 v1( 20.0, 75.5 );
		Vector2 v2( 5.0, 2.0 );
		Vector2 v3( v1 * v2 );

		f32 eX = 100.0;
		f32 eY = 151.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
	}

	void testMultScalar()
	{
		Vector2 v1( 20.0, 75.5 );
		f32 scalar = 2.0;
		Vector2 v2( v1 * scalar );

		f32 eX = 40.0;
		f32 eY = 151.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v2[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v2[BK_Y] ) );
	}

	void testEqual()
	{
		Vector2 v1( 3.0, 6.0 );
		Vector2 v2( 3.0, 6.0 );

		CPPUNIT_ASSERT( v1 == v2 );
	}

	void testNotEqual()
	{
		Vector2 v1( 3.0, 5.0 );
		Vector2 v2( 3.0, 6.0 );

		CPPUNIT_ASSERT( v1 != v2 );
	}

	void testDivVec2()
	{
		Vector2 v1( 10.0, 15.0 );
		Vector2 v2(  0.0,  3.0 );
		Vector2 v3( v1 / v2 );

		f32 eX = FLT_MAX;
		f32 eY = 5.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
	}

	void testDivScalar()
	{
		Vector2 v1( 10.0, 15.0 );
		f32 scalar = 2.0;
		Vector2 v3( v1 / scalar );

		f32 eX = 5.0;
		f32 eY = 7.5;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
	}

	void testMag()
	{
		Vector2 v1( 5.0, 23.0 );
		f32 m = v1.mag();

		f32 ex = sqrt( 5.0 * 5.0 + 23.0 * 23.0 );

		CPPUNIT_ASSERT_EQUAL( ex, m );
		CPPUNIT_ASSERT_EQUAL( ex, v1.mag() );
	}

	void testMagSqr()
	{
		Vector2 v1( 5.0, 20.0 );
		f32 m = v1.magSqr();

		f32 ex = 425.0;

		CPPUNIT_ASSERT_EQUAL( ex, m );
	}

	void testNormalised()
	{
		Vector2 v1( 5.0, 100.0 );
		Vector2 vNorm( v1.normalised() );

		f32 eMag = 1.0;
		f32 tolerance = 0.0000001;

		CPPUNIT_ASSERT( fabs( eMag - vNorm.mag() ) < tolerance );
	}

	void testNormalise()
	{
		Vector2 v1( 10.5, 234.345 );
		f32 eNorm = 1.0;
		f32 tolerance = 0.0000001;

		CPPUNIT_ASSERT( fabs( eNorm - v1.normalise().mag() ) < tolerance );
	}

	void testDot()
	{
		Vector2 v1( 5.0, 20.0 );
		Vector2 v2( 10.0, 45.0 );

		f32 m = v1.dot( v2 );

		f32 ex = 950.0;

		CPPUNIT_ASSERT_EQUAL( ex, m );
	}
};

#endif /* end of include guard: VECTOR2_TEST_H_8EFWUNPO */

