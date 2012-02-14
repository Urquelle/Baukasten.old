#ifndef IMAGE_TEST_H_S4PR5FHA
#define IMAGE_TEST_H_S4PR5FHA

#include "model/Global"
#include "graphics/Image"

using namespace Baukasten;
using namespace CppUnit;

class ImageTest : public TestFixture {
	CPPUNIT_TEST_SUITE( ImageTest );
	CPPUNIT_TEST( testFileExists );
	CPPUNIT_TEST( testFileType );
	CPPUNIT_TEST( testFileClose );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
		path = "/home/serge.ratke/projekte/cpp/baukasten/example/tetris/media/display.png";
	}

	void tearDown()
	{
		image->close();
	}

	void testFileExists()
	{
		image = new Image(path);

		CPPUNIT_ASSERT_EQUAL( true, image->isOpen() );
	}

	void testFileType()
	{
		image = new Image(path);

		CPPUNIT_ASSERT_EQUAL( Image::PNG, image->type() );
	}

	void testFileClose()
	{
		image = new Image(path);
		image->close();

		CPPUNIT_ASSERT_EQUAL( false, image->isOpen() );
	}

private:
	string path;
	Image* image;
};

#endif /* end of include guard: IMAGE_TEST_H_S4PR5FHA */

