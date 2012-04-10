#ifndef GAME_ENTITY_TEST_H_GSWLEI6S
#define GAME_ENTITY_TEST_H_GSWLEI6S

#include "model/GameEntity"
#include "model/ModelInterface"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace Baukasten;
using namespace CppUnit;

class GameEntityTest : public TestFixture {
	CPPUNIT_TEST_SUITE( GameEntityTest );
	CPPUNIT_TEST( testCreate );
	CPPUNIT_TEST( testDestroy );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
	}

	void tearDown()
	{
		ModelInterface::instance().shutdown();
	}

	void testCreate()
	{
		ModelInterface &model = ModelInterface::instance();

		GameEntity *e = model.createEntity( "test:entity" );
		string expected = "test:entity";
		u32 uniqueId = 1;

		CPPUNIT_ASSERT_EQUAL( expected, e->id() );
		CPPUNIT_ASSERT_EQUAL( uniqueId, model.uniqueId( e ) );
	}

	void testDestroy()
	{
		ModelInterface &model = ModelInterface::instance();

		GameEntity *e = model.createEntity( "test:entity" );
		string expected = "test:entity";
		CPPUNIT_ASSERT_EQUAL( expected, e->id() );

		model.destroyEntity( model.uniqueId( e ) );
		u32 count = 0;
		CPPUNIT_ASSERT_EQUAL( count, model.entityCount() );
	}
};

#endif /* end of include guard: GAME_ENTITY_TEST_H_GSWLEI6S */

