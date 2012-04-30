#ifndef TIMER_TEST_H_Z5YQV8SI
#define TIMER_TEST_H_Z5YQV8SI

#include "core/Timer"
#include "core/TimerInterface"

using namespace Baukasten;
using namespace CppUnit;

/*!
 * \brief TimerTest class declaration.
 */
class TimerTest : public TestFixture {
	CPPUNIT_TEST_SUITE( TimerTest );
	CPPUNIT_TEST( testStart );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
	}

	void tearDown()
	{
	}

	void testStart()
	{
		Timer &t = TimerInterface::instance()->createTimer( "main" );

		t.start();

		for ( size_t i = 0; i < 100000000; ++i ) {
		}
		t.update();
		u64 t1 = t.cycles();
		f32 tt1 = t.time();

		for ( size_t i = 0; i < 100000000; ++i ) {
		}
		t.update();
		u64 t2 = t.cycles();
		f32 tt2 = t.time();

		CPPUNIT_ASSERT( t2 > t1 );
	}

private:
	/* data */
};

#endif /* end of include guard: TIMER_TEST_H_Z5YQV8SI */

