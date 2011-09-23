#ifndef ACTION_TEST_5J551I3N
#define ACTION_TEST_5J551I3N

#include <action_manager.h>
#include <entity.h>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Baukasten;
using namespace CppUnit;

class ActionManagerTest : public TestFixture {
	CPPUNIT_TEST_SUITE( ActionManagerTest );
	CPPUNIT_TEST( testHasAction );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
		actionManager = new ActionManager();
	}

	void tearDown()
	{
		delete actionManager;
	}

	void testHasAction()
	{
		CPPUNIT_ASSERT_EQUAL( false, actionManager->hasAction( "action:test" ) );
	}

private:
	ActionManager *actionManager;
};

#endif /* end of include guard: ACTION_TEST_5J551I3N */

