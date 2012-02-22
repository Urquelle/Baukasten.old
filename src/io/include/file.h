#ifndef FILE_H_AREGWB6S
#define FILE_H_AREGWB6S

#include "io/Global"

namespace Baukasten {
	class FilePrivate;

	class File {
	public:
		File( const char* );
		File( const string& );

		virtual ~File();

		void   close();
		bool   isOpen() const;
		void   open();
		void   read( char*, const u32 );
		u32    size() const;

	private:
		BK_PIMPL_PTR( File );
	};
} /* Baukasten  */

#endif /* end of include guard: FILE_H_AREGWB6S */

