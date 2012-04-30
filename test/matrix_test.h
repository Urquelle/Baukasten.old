#ifndef MATRIX_TEST_H_QJURYESZ
#define MATRIX_TEST_H_QJURYESZ

#include "core/Debug"
#include "math/Matrix"
#include "math/Quaternion"
#include "math/Vector3"

using namespace Baukasten;
using namespace CppUnit;

/*!
 * \brief MatrixTest class declaration.
 */
class MatrixTest : public TestFixture {
	CPPUNIT_TEST_SUITE( MatrixTest );
	CPPUNIT_TEST( testInitEmpty );
	CPPUNIT_TEST( testInitInitializerList );
	CPPUNIT_TEST( testInitMatrix );
	CPPUNIT_TEST( testAddScalar );
	CPPUNIT_TEST( testAddMatrix );
	CPPUNIT_TEST( testMultScalar );
	CPPUNIT_TEST( testMultMatrix );
	CPPUNIT_TEST( testStaticAddScalar );
	CPPUNIT_TEST( testStaticAddMatrix );
	CPPUNIT_TEST( testStaticSubtractScalar );
	CPPUNIT_TEST( testStaticSubtractMatrix );
	CPPUNIT_TEST( testDet );
	CPPUNIT_TEST( testScale );
	CPPUNIT_TEST( testTranslation );
	CPPUNIT_TEST( testRotation );
	CPPUNIT_TEST_SUITE_END();
public:

	void testInitEmpty()
	{
		Matrix *m = new Matrix();

		f32 e11, e22, e33, e44;
		e11 = e22 = e33 = e44 = 1.0f;

		CPPUNIT_ASSERT_EQUAL( e11, static_cast<f32>( (*m)[Matrix::M11] ) );
		CPPUNIT_ASSERT_EQUAL( e22, static_cast<f32>( (*m)[Matrix::M22] ) );
		CPPUNIT_ASSERT_EQUAL( e33, static_cast<f32>( (*m)[Matrix::M33] ) );
		CPPUNIT_ASSERT_EQUAL( e44, static_cast<f32>( (*m)[Matrix::M44] ) );

		delete m;
	}

	void testInitInitializerList()
	{
		// matrix in column form
		Matrix *m = new Matrix({
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
		});

		f32 e11, e21, e31, e41, e12, e22, e32, e42,
			e13, e23, e33, e43, e14, e24, e34, e44;

		e11 = 1.0f;
		e12 = 2.0f;
		e13 = 3.0f;
		e14 = 4.0f;
		e21 = 5.0f;
		e22 = 6.0f;
		e23 = 7.0f;
		e24 = 8.0f;
		e31 = 9.0f;
		e32 = 10.0f;
		e33 = 11.0f;
		e34 = 12.0f;
		e41 = 13.0f;
		e42 = 14.0f;
		e43 = 15.0f;
		e44 = 16.0f;

		CPPUNIT_ASSERT_EQUAL( e11, m->get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( e12, m->get( Matrix::M12 ) );
		CPPUNIT_ASSERT_EQUAL( e13, m->get( Matrix::M13 ) );
		CPPUNIT_ASSERT_EQUAL( e14, m->get( Matrix::M14 ) );
		CPPUNIT_ASSERT_EQUAL( e21, m->get( Matrix::M21 ) );
		CPPUNIT_ASSERT_EQUAL( e22, m->get( Matrix::M22 ) );
		CPPUNIT_ASSERT_EQUAL( e23, m->get( Matrix::M23 ) );
		CPPUNIT_ASSERT_EQUAL( e24, m->get( Matrix::M24 ) );
		CPPUNIT_ASSERT_EQUAL( e31, m->get( Matrix::M31 ) );
		CPPUNIT_ASSERT_EQUAL( e32, m->get( Matrix::M32 ) );
		CPPUNIT_ASSERT_EQUAL( e33, m->get( Matrix::M33 ) );
		CPPUNIT_ASSERT_EQUAL( e34, m->get( Matrix::M34 ) );
		CPPUNIT_ASSERT_EQUAL( e41, m->get( Matrix::M41 ) );
		CPPUNIT_ASSERT_EQUAL( e42, m->get( Matrix::M42 ) );
		CPPUNIT_ASSERT_EQUAL( e43, m->get( Matrix::M43 ) );
		CPPUNIT_ASSERT_EQUAL( e44, m->get( Matrix::M44 ) );

		delete m;
	}

	void testInitMatrix()
	{
		Matrix *m = new Matrix({
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
		});

		Matrix *m2 = new Matrix( *m );

		f32 e11, e21, e31, e41, e12, e22, e32, e42,
			e13, e23, e33, e43, e14, e24, e34, e44;

		e11 = 1.0f;
		e12 = 2.0f;
		e13 = 3.0f;
		e14 = 4.0f;
		e21 = 5.0f;
		e22 = 6.0f;
		e23 = 7.0f;
		e24 = 8.0f;
		e31 = 9.0f;
		e32 = 10.0f;
		e33 = 11.0f;
		e34 = 12.0f;
		e41 = 13.0f;
		e42 = 14.0f;
		e43 = 15.0f;
		e44 = 16.0f;

		CPPUNIT_ASSERT_EQUAL( e11, m2->get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( e12, m2->get( Matrix::M12 ) );
		CPPUNIT_ASSERT_EQUAL( e13, m2->get( Matrix::M13 ) );
		CPPUNIT_ASSERT_EQUAL( e14, m2->get( Matrix::M14 ) );
		CPPUNIT_ASSERT_EQUAL( e21, m2->get( Matrix::M21 ) );
		CPPUNIT_ASSERT_EQUAL( e22, m2->get( Matrix::M22 ) );
		CPPUNIT_ASSERT_EQUAL( e23, m2->get( Matrix::M23 ) );
		CPPUNIT_ASSERT_EQUAL( e24, m2->get( Matrix::M24 ) );
		CPPUNIT_ASSERT_EQUAL( e31, m2->get( Matrix::M31 ) );
		CPPUNIT_ASSERT_EQUAL( e32, m2->get( Matrix::M32 ) );
		CPPUNIT_ASSERT_EQUAL( e33, m2->get( Matrix::M33 ) );
		CPPUNIT_ASSERT_EQUAL( e34, m2->get( Matrix::M34 ) );
		CPPUNIT_ASSERT_EQUAL( e41, m2->get( Matrix::M41 ) );
		CPPUNIT_ASSERT_EQUAL( e42, m2->get( Matrix::M42 ) );
		CPPUNIT_ASSERT_EQUAL( e43, m2->get( Matrix::M43 ) );
		CPPUNIT_ASSERT_EQUAL( e44, m2->get( Matrix::M44 ) );

		delete m;
		delete m2;
	}

	void testAddScalar()
	{
		Matrix *m = new Matrix( Matrix::zero() );
		m->add( 5.5f );

		f32 ex = 5.5f;

		CPPUNIT_ASSERT_EQUAL( ex, m->get( Matrix::M11 ) );
	}

	void testAddMatrix()
	{
		Matrix m = Matrix::zero();
		Matrix m2 = Matrix::identity();

		m.add( m2 );

		f32 ex = 1.0f;

		CPPUNIT_ASSERT_EQUAL( ex, m.get( Matrix::M11 ) );
	}

	void testMultScalar()
	{
		Matrix m = Matrix::identity();

		m.multiply( 3.5f );
		f32 ex = 3.5f;

		CPPUNIT_ASSERT_EQUAL( ex, m.get( Matrix::M11 ) );
	}

	void testMultMatrix()
	{
		Matrix m = Matrix({
			1,  2,  3,  4,
			5,  6,  7,  8,
			9,  10, 11, 12,
			13, 14, 15, 16
		});

		Matrix m2 = Matrix({
			2,   2.5,  1,   3,
			0.5, 5.3,  0.3, 4.7,
			10,  10.5, 2,   2,
			2,   2,    2,   2
		});

		m.multiply( m2 );

		f32 ex11 = 1*2 + 5*2.5 + 9 *1 + 13*3;
		f32 ex12 = 2*2 + 6*2.5 + 10*1 + 14*3;
		f32 ex13 = 3*2 + 7*2.5 + 11*1 + 15*3;
		f32 ex14 = 4*2 + 8*2.5 + 12*1 + 16*3;

		f32 ex21 = 1*0.5 + 5*5.3 + 9 *0.3 + 13*4.7;
		f32 ex22 = 2*0.5 + 6*5.3 + 10*0.3 + 14*4.7;
		f32 ex23 = 3*0.5 + 7*5.3 + 11*0.3 + 15*4.7;
		f32 ex24 = 4*0.5 + 8*5.3 + 12*0.3 + 16*4.7;

		f32 ex31 = 1*10 + 5*10.5 + 9 *2 + 13*2;
		f32 ex32 = 2*10 + 6*10.5 + 10*2 + 14*2;
		f32 ex33 = 3*10 + 7*10.5 + 11*2 + 15*2;
		f32 ex34 = 4*10 + 8*10.5 + 12*2 + 16*2;

		f32 ex41 = 1*2 + 5*2 + 9 *2 + 13*2;
		f32 ex42 = 2*2 + 6*2 + 10*2 + 14*2;
		f32 ex43 = 3*2 + 7*2 + 11*2 + 15*2;
		f32 ex44 = 4*2 + 8*2 + 12*2 + 16*2;

		CPPUNIT_ASSERT_EQUAL( ex11, m.get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( ex12, m.get( Matrix::M12 ) );
		CPPUNIT_ASSERT_EQUAL( ex13, m.get( Matrix::M13 ) );
		CPPUNIT_ASSERT_EQUAL( ex14, m.get( Matrix::M14 ) );

		CPPUNIT_ASSERT_EQUAL( ex21, m.get( Matrix::M21 ) );
		CPPUNIT_ASSERT_EQUAL( ex22, m.get( Matrix::M22 ) );
		CPPUNIT_ASSERT_EQUAL( ex23, m.get( Matrix::M23 ) );
		CPPUNIT_ASSERT_EQUAL( ex24, m.get( Matrix::M24 ) );

		CPPUNIT_ASSERT_EQUAL( ex31, m.get( Matrix::M31 ) );
		CPPUNIT_ASSERT_EQUAL( ex32, m.get( Matrix::M32 ) );
		CPPUNIT_ASSERT_EQUAL( ex33, m.get( Matrix::M33 ) );
		CPPUNIT_ASSERT_EQUAL( ex34, m.get( Matrix::M34 ) );

		CPPUNIT_ASSERT_EQUAL( ex41, m.get( Matrix::M41 ) );
		CPPUNIT_ASSERT_EQUAL( ex42, m.get( Matrix::M42 ) );
		CPPUNIT_ASSERT_EQUAL( ex43, m.get( Matrix::M43 ) );
		CPPUNIT_ASSERT_EQUAL( ex44, m.get( Matrix::M44 ) );
	}

	void testStaticAddScalar()
	{
		Matrix m;
		Matrix::add( 3.0, m, &m );

		f32 ex11 = 4.0;
		f32 ex12 = 3.0;

		CPPUNIT_ASSERT_EQUAL( ex11, m.get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( ex12, m.get( Matrix::M12 ) );
	}

	void testStaticAddMatrix()
	{
		Matrix m, m2;
		Matrix::add( m, m2, &m );

		f32 ex11 = 2.0;
		f32 ex12 = 0.0;

		CPPUNIT_ASSERT_EQUAL( ex11, m.get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( ex12, m.get( Matrix::M12 ) );
	}

	void testStaticSubtractScalar()
	{
		Matrix m = {
			5,  6,  1,   3,
			4,  5,  10,  7,
			2,  9,  25,  23,
			11, 33, 0.5, 6
		};

		m.subtract( 3.0 );

		f32 ex11 = 2.0;
		f32 ex12 = 3.0;

		CPPUNIT_ASSERT_EQUAL( ex11, m.get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( ex12, m.get( Matrix::M12 ) );
	}

	void testStaticSubtractMatrix()
	{
		Matrix m = {
			5,  6,  1,   3,
			4,  5,  10,  7,
			2,  9,  25,  23,
			11, 33, 0.5, 6
		};

		Matrix m2 = {
			3,  6,  0,   3,
			1,  5,  5.0,  7,
			-2,  9,  25,  23,
			11, 33, 0.5, 6
		};

		m.subtract( m2 );

		f32 ex11 = 2.0;
		f32 ex12 = 0.0;
		f32 ex13 = 1.0;

		CPPUNIT_ASSERT_EQUAL( ex11, m.get( Matrix::M11 ) );
		CPPUNIT_ASSERT_EQUAL( ex12, m.get( Matrix::M12 ) );
		CPPUNIT_ASSERT_EQUAL( ex13, m.get( Matrix::M13 ) );
	}

	void testDet()
	{
		Matrix m = {
			1,  2,  -3,  4,
			0,  4,   5,  1,
			1,  1,   0,  2,
			-1, 3,   4,  0
		};

		f32 ex = 10.0f;

		CPPUNIT_ASSERT_EQUAL( ex, m.det() );
	}

	void testScale()
	{
		Matrix m = {
			1, 0,   0,   0,
			0, 1.5, 0.7, 0,
			0, 0.3, 1,   0,
			2, 3,   4,   1
		};

		Vector3 scale;
		m.decompose( &scale, NULL, NULL );

		Vector3 eScale = {
			Vector3{ 1, 0,   0   }.mag(),
			Vector3{ 0, 1.5, 0.7 }.mag(),
			Vector3{ 0, 0.3, 1   }.mag()
		};

		CPPUNIT_ASSERT_EQUAL( eScale.x, scale.x );
		CPPUNIT_ASSERT_EQUAL( eScale.y, scale.y );
		CPPUNIT_ASSERT_EQUAL( eScale.z, scale.z );
	}

	void testTranslation()
	{
		Matrix m = {
			1, 0,   0,   0,
			0, 1.5, 0.7, 0,
			0, 0.3, 1,   0,
			2, 3,   4,   1
		};

		Vector3 translation;
		m.decompose( NULL, &translation, NULL );

		Vector3 eTr = { 2, 3, 4 };

		CPPUNIT_ASSERT_EQUAL( eTr.x, translation.x );
		CPPUNIT_ASSERT_EQUAL( eTr.y, translation.y );
		CPPUNIT_ASSERT_EQUAL( eTr.z, translation.z );
	}

	void testRotation()
	{
		Matrix m = {
			1, 0,   0,   0,
			0, 0.5, 0.7, 0,
			0, 0.3, 0.2, 0,
			2, 3,   4,   1
		};

		Quaternion rotation;
		m.decompose( NULL, NULL, &rotation );

		BK_DEBUG( "rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << " " << rotation.w );
	}
};

#endif /* end of include guard: MATRIX_TEST_H_QJURYESZ */

