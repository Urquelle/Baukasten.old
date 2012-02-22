#ifndef FILE_TEST_H_QQU2SEFY
#define FILE_TEST_H_QQU2SEFY

#include "io/File"

using namespace Baukasten;
using namespace CppUnit;

class FileTest : public TestFixture {
	CPPUNIT_TEST_SUITE( FileTest );
	CPPUNIT_TEST( testOpenFile );
	CPPUNIT_TEST( testCloseFile );
	CPPUNIT_TEST( testSize );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
		m_path = "files/file_test.txt";
		m_file = new File( m_path );
	}

	void tearDown()
	{
		m_file->close();
		delete m_file;
	}

	void testOpenFile()
	{
		bool expected = true;

		m_file->open();

		CPPUNIT_ASSERT_EQUAL( expected, m_file->isOpen() );
	}

	void testCloseFile()
	{
		bool expected = false;

		m_file->open();
		m_file->close();

		CPPUNIT_ASSERT_EQUAL( expected, m_file->isOpen() );
	}

	void testSize()
	{
		u32 expected = 41;

		m_file->open();

		CPPUNIT_ASSERT_EQUAL( expected, m_file->size() );
	}

private:
	char* m_path;
	File* m_file;
};

#endif /* end of include guard: FILE_TEST_H_QQU2SEFY */

