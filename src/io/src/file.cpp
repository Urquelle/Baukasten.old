#include "io/File"

#include <iostream>
#include <fstream>

using namespace Baukasten;

// FilePrivate {{{
namespace Baukasten {
	class FilePrivate {
	public:
		FilePrivate( const char *path ) :
			m_size( 0 ),
			m_path( path )
		{
		}

		virtual ~FilePrivate()
		{
			m_file.close();
		}

		void
		close()
		{
			m_file.close();
		}

		bool
		isOpen() const
		{
			return m_file.is_open();
		}

		void
		open()
		{
			m_file.open( m_path );
			m_file.seekg( 0, ios::end );
			m_size = m_file.tellg();
			m_file.seekg( 0, ios::beg );
		}

		void
		read( char *buffer, const u32 size )
		{
			if ( !isOpen() )
				return;

			m_file.read( buffer, size );
		}

		u32
		size() const
		{
			return m_size;
		}

	private:
		fstream     m_file;
		u32         m_size;
		const char* m_path;
	};
} /* Baukasten  */
// }}}

File::File( const char *path ) :
	m_impl( new FilePrivate( path ) )
{
}

File::File( const string &path ) :
	m_impl( new FilePrivate( path.c_str() ) )
{
}

File::~File()
{
	delete m_impl;
}

void
File::close()
{
	m_impl->close();
}

bool
File::isOpen() const
{
	return m_impl->isOpen();
}

void
File::open()
{
	m_impl->open();
}

void
File::read( char *buffer, const u32 size )
{
	m_impl->read( buffer, size );
}

u32
File::size() const
{
	return m_impl->size();
}

