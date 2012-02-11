#ifndef ENTITY_TEST_WM92AXC3
#define ENTITY_TEST_WM92AXC3

#include <entity.h>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Baukasten;
using namespace CppUnit;

class EntityTest : public TestFixture {
	CPPUNIT_TEST_SUITE( EntityTest );
	CPPUNIT_TEST( testId );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
		entity = new Entity( "entity:test" );
	}

	void tearDown()
	{
		delete entity;
	}

	void testId()
	{
		string expected = "entity:test";
		CPPUNIT_ASSERT_EQUAL( expected, entity->id() );
	}

private:
	Entity *entity;
};

#endif /* end of include guard: ENTITY_TEST_WM92AXC3 */
