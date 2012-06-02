#include "actionmanager_test.h"
#include "color_test.h"
#include "entity_test.h"
#include "file_test.h"
#include "game_entity_test.h"
#include "image_test.h"
#include "matrix_test.h"
#include "random_test.h"
#include "timer_test.h"
#include "vector_test.h"
#include "vector2_test.h"
#include "vector3_test.h"

#include <cppunit/ui/text/TestRunner.h>

int main(int argc, const char *argv[])
{

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( ActionManagerTest::suite() );
	runner.addTest( ColorTest::suite() );
	runner.addTest( EntityTest::suite() );
	runner.addTest( FileTest::suite() );
	runner.addTest( GameEntityTest::suite() );
	runner.addTest( ImageTest::suite() );
	runner.addTest( MatrixTest::suite() );
	runner.addTest( RandomTest::suite() );
	runner.addTest( TimerTest::suite() );
	runner.addTest( VectorTest::suite() );
	runner.addTest( Vector2Test::suite() );
	runner.addTest( Vector3Test::suite() );
	runner.run();
	return 0;
}
