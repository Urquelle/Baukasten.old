#include "entity_test.h"
#include "actionmanager_test.h"

#include <cppunit/ui/text/TestRunner.h>

int main(int argc, const char *argv[])
{

	CppUnit::TextUi::TestRunner runner;
	runner.addTest( EntityTest::suite() );
	runner.addTest( ActionManagerTest::suite() );
	runner.run();
	return 0;
}
