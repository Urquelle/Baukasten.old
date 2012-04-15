#ifndef VECTOR_TEST_H_LN9XNQUF
#define VECTOR_TEST_H_LN9XNQUF

#include "math/Vector"

using namespace Baukasten;
using namespace CppUnit;

/*!
 * \break VectorTest class declaration.
 */
class VectorTest : public TestFixture {
	CPPUNIT_TEST_SUITE( VectorTest );
	CPPUNIT_TEST( testInit );
	CPPUNIT_TEST( testAssign );
	CPPUNIT_TEST( testCopyCtor );
	CPPUNIT_TEST( testAssignOpVec );
	CPPUNIT_TEST( testAssignOpScalar );
	CPPUNIT_TEST( testPlusOpVec );
	CPPUNIT_TEST( testPlusOpScalar );
	CPPUNIT_TEST( testMultOpVec );
	CPPUNIT_TEST( testMultOpScalar );
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
		Vector<u32, 3> v;

		u32 eX = 0;
		u32 eY = 0;
		u32 eZ = 0;

		CPPUNIT_ASSERT_EQUAL( eX, static_cast<u32>( v[BK_X] ) );
		CPPUNIT_ASSERT_EQUAL( eY, static_cast<u32>( v[BK_Y] ) );
		CPPUNIT_ASSERT_EQUAL( eZ, static_cast<u32>( v[BK_Z] ) );
	}

	void testAssign()
	{
		Vector<u32, 5> v;

		v[0] = 1; u32 e1 = 1;
		v[1] = 2; u32 e2 = 2;
		v[2] = 3; u32 e3 = 3;
		v[3] = 4; u32 e4 = 4;
		v[4] = 5; u32 e5 = 5;

		CPPUNIT_ASSERT_EQUAL( e1, static_cast<u32>( v[0] ) );
		CPPUNIT_ASSERT_EQUAL( e2, static_cast<u32>( v[1] ) );
		CPPUNIT_ASSERT_EQUAL( e3, static_cast<u32>( v[2] ) );
		CPPUNIT_ASSERT_EQUAL( e4, static_cast<u32>( v[3] ) );
		CPPUNIT_ASSERT_EQUAL( e5, static_cast<u32>( v[4] ) );
	}

	void testCopyCtor()
	{
		Vector<u32, 5> v;

		v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; v[4] = 5;
		u32 e1 = 1, e2 = 2, e3 = 3, e4 = 4, e5 = 5;

		Vector<u32, 5> v2( v );

		CPPUNIT_ASSERT_EQUAL( e1, static_cast<u32>( v2[0] ) );
		CPPUNIT_ASSERT_EQUAL( e2, static_cast<u32>( v2[1] ) );
		CPPUNIT_ASSERT_EQUAL( e3, static_cast<u32>( v2[2] ) );
		CPPUNIT_ASSERT_EQUAL( e4, static_cast<u32>( v2[3] ) );
		CPPUNIT_ASSERT_EQUAL( e5, static_cast<u32>( v2[4] ) );
	}

	void testAssignOpVec()
	{
		Vector<u32, 5> v1, v2;

		v2[0] = 1; v2[1] = 2; v2[2] = 3; v2[3] = 4; v2[4] = 5;

		v1 = v2;

		u32 e1 = 1, e2 = 2, e3 = 3, e4 = 4, e5 = 5;

		CPPUNIT_ASSERT_EQUAL( e1, static_cast<u32>( v1[0] ) );
		CPPUNIT_ASSERT_EQUAL( e2, static_cast<u32>( v1[1] ) );
		CPPUNIT_ASSERT_EQUAL( e3, static_cast<u32>( v1[2] ) );
		CPPUNIT_ASSERT_EQUAL( e4, static_cast<u32>( v1[3] ) );
		CPPUNIT_ASSERT_EQUAL( e5, static_cast<u32>( v1[4] ) );
	}

	void testAssignOpScalar()
	{
		Vector<u32, 5> v1;

		v1 = 3;
		u32 e = 3;

		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[0] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[1] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[2] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[3] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[4] ) );
	}

	void testPlusOpVec()
	{
		Vector<u32, 5> v1, v2;

		v1 = 7;
		v2 = 3;
		v2 = v2 + v1;
		u32 e = 10;

		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[0] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[1] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[2] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[3] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[4] ) );
	}

	void testPlusOpScalar()
	{
		Vector<u32, 5> v1;

		v1 = 7;
		v1 = v1 + 3;
		u32 e = 10;

		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[0] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[1] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[2] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[3] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[4] ) );
	}

	void testMultOpVec()
	{
		Vector<u32, 5> v1, v2;

		v1 = 7;
		v2 = 3;
		v2 = v2 * v1;
		u32 e = 21;

		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[0] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[1] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[2] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[3] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v2[4] ) );
	}

	void testMultOpScalar()
	{
		Vector<u32, 5> v1;

		v1 = 7;
		v1 = v1 * 3;
		u32 e = 21;

		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[0] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[1] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[2] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[3] ) );
		CPPUNIT_ASSERT_EQUAL( e, static_cast<u32>( v1[4] ) );
	}
};

#endif /* end of include guard: VECTOR_TEST_H_LN9XNQUF */

