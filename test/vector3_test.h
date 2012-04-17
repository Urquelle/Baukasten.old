#ifndef VECTOR3_TEST_H_YI2AUPWF
#define VECTOR3_TEST_H_YI2AUPWF

#include "math/Vector3"

using namespace Baukasten;
using namespace CppUnit;

/*!
 * \break Vector3Test class declaration.
 */
class Vector3Test : public TestFixture {
	CPPUNIT_TEST_SUITE( Vector3Test );
	CPPUNIT_TEST( testInit );
	CPPUNIT_TEST( testCopyConstructor );
	CPPUNIT_TEST( testAdditionVec3 );
	CPPUNIT_TEST( testAdditionScalar );
	CPPUNIT_TEST( testMultVec3 );
	CPPUNIT_TEST( testMultScalar );
	CPPUNIT_TEST( testEqual );
	CPPUNIT_TEST( testNotEqual );
	CPPUNIT_TEST( testDivVec3 );
	CPPUNIT_TEST( testDivScalar );
	CPPUNIT_TEST( testMag );
	CPPUNIT_TEST( testMagSqr );
	CPPUNIT_TEST( testNormalised );
	CPPUNIT_TEST( testNormalise );
	CPPUNIT_TEST( testDot );
	CPPUNIT_TEST( testCross );
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
		Vector3 v( 1.0, 2.0, 3.0 );

		f32 expectedX = 1.0;
		f32 expectedY = 2.0;
		f32 expectedZ = 3.0;

		CPPUNIT_ASSERT_EQUAL( expectedX, static_cast<f32>( v[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( expectedY, static_cast<f32>( v[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( expectedZ, static_cast<f32>( v[BK_Z] ) );
	}

	void testCopyConstructor()
	{
		Vector3 v1( 5, 10, 12 );
		Vector3 v2 = v1;

		f32 eX = 5;
		f32 eY = 10;
		f32 eZ = 12;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v2[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v2[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v2[BK_Z] ) );
	}

	void testAdditionVec3()
	{
		Vector3 v1( 2.0, 4.0, 6.0 );
		Vector3 v2( 3.0, 6.0, 9.0 );
		Vector3 v3 = v1 + v2;

		f32 eX = 5.0;
		f32 eY = 10.0;
		f32 eZ = 15.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v3[BK_Z] ) );
	}

	void testAdditionScalar()
	{
		Vector3 v1( 2.0, 4.0, 6.0 );
		f32 scalar = 1.5;

		Vector3 v2( v1 + scalar );

		f32 eX = 3.5;
		f32 eY = 5.5;
		f32 eZ = 7.5;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v2[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v2[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v2[BK_Z] ) );
	}

	void testMultVec3()
	{
		Vector3 v1( 20.0, 75.5, 101.0 );
		Vector3 v2( 5.0, 2.0, 11.0 );
		Vector3 v3( v1 * v2 );

		f32 eX = 100.0;
		f32 eY = 151.0;
		f32 eZ = 1111.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v3[BK_Z] ) );
	}

	void testMultScalar()
	{
		Vector3 v1( 20.0, 75.5, 53.0 );
		f32 scalar = 2.0;
		Vector3 v2( v1 * scalar );

		f32 eX = 40.0;
		f32 eY = 151.0;
		f32 eZ = 106.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v2[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v2[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v2[BK_Z] ) );
	}

	void testEqual()
	{
		Vector3 v1( 3.0, 6.0, 9.15 );
		Vector3 v2( 3.0, 6.0, 9.15 );

		CPPUNIT_ASSERT( v1 == v2 );
	}

	void testNotEqual()
	{
		Vector3 v1( 3.0, 5.0, 75.0 );
		Vector3 v2( 3.0, 6.0, 75.0 );

		CPPUNIT_ASSERT( v1 != v2 );
	}

	void testDivVec3()
	{
		Vector3 v1( 10.0, 15.0, 99.0 );
		Vector3 v2(  0.0,  3.0, 11.0 );
		Vector3 v3( v1 / v2 );

		f32 eX = FLT_MAX;
		f32 eY = 5.0;
		f32 eZ = 9.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v3[BK_Z] ) );
	}

	void testDivScalar()
	{
		Vector3 v1( 10.0, 15.0, 20.0 );
		f32 scalar = 2.0;
		Vector3 v3( v1 / scalar );

		f32 eX = 5.0;
		f32 eY = 7.5;
		f32 eZ = 10.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( v3[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( v3[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( v3[BK_Z] ) );
	}

	void testMag()
	{
		Vector3 v1( 5.0, 23.0, 11.0 );
		f32 m = v1.mag();

		f32 ex = sqrt( 5.0 * 5.0 + 23.0 * 23.0 + 11.0 * 11.0 );

		CPPUNIT_ASSERT_EQUAL( ex, m );
		CPPUNIT_ASSERT_EQUAL( ex, v1.mag() );
	}

	void testMagSqr()
	{
		Vector3 v1( 5.0, 20.0, 19.0 );
		f32 m = v1.magSqr();

		f32 ex = 786.0;

		CPPUNIT_ASSERT_EQUAL( ex, m );
	}

	void testNormalised()
	{
		Vector3 v1( 5.0, 100.0, 13.0 );
		Vector3 vNorm( v1.normalised() );

		f32 eMag = 1.0;
		f32 tolerance = 0.0000001;

		CPPUNIT_ASSERT( fabs( eMag - vNorm.mag() ) < tolerance );
	}

	void testNormalise()
	{
		Vector3 v1( 10.5, 234.345, 0.5 );
		f32 eNorm = 1.0;
		f32 tolerance = 0.000001;
		f32 res = v1.normalise().mag();

		CPPUNIT_ASSERT( fabs( eNorm - res ) < tolerance );
	}

	void testDot()
	{
		Vector3 v1( 5.0, 20.0, 71.0 );
		Vector3 v2( 10.0, 45.0, 44.0 );

		f32 m = v1.dot( v2 );

		f32 ex = 4074.0;

		CPPUNIT_ASSERT_EQUAL( ex, m );
	}

	void testCross()
	{
		Vector3 v1( 15.0, 434.0, 1.0 );
		Vector3 v2( 1.0, 53.0, 71.5 );
		Vector3 cross( v1.cross( v2 ) );

		f32 eX = 30978;
		f32 eY = -1071.5;
		f32 eZ = 361.0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<f32>( cross[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<f32>( cross[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<f32>( cross[BK_Z] ) );
	}
};

#endif /* end of include guard: VECTOR3_TEST_H_YI2AUPWF */

