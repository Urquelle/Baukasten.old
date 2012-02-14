#include "actionmanager_test.h"
#include "color_test.h"
#include "entity_test.h"
#include "image_test.h"
#include "math_test.h"

#include <cppunit/ui/text/TestRunner.h>

int main(int argc, const char *argv[])
{

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( ActionManagerTest::suite() );
	runner.addTest( ColorTest::suite() );
	runner.addTest( EntityTest::suite() );
	runner.addTest( MathTest::suite() );
	runner.addTest( ImageTest::suite() );
	runner.run();
	return 0;
}
