#include "graphics/Image"

#include "model/Debug"

#include <png.h>
#include <cstdlib>

using namespace Baukasten;

struct ImageInfo {
	u32 size, width, height, numberOfPasses, bitDepth;
	bool alpha;
	u8* data;
};

Image::ImageType
type( FILE *f )
{
	Image::ImageType t = Image::NO_TYPE;

	// check for png
	png_byte header[8];
	fread( header, 1, 8, f );
	if ( !png_sig_cmp( header, 0, 8 ) ) {
		t = Image::PNG;
	}

	return t;
}

bool readPng( FILE *fp, ImageInfo *info )
{
	png_structp png_ptr;
	png_infop info_ptr;
	u32 sig_read = 8;

	if ( !fp )
		BK_ERROR( "invalid file handle" );

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
			NULL, NULL, NULL);

	if (png_ptr == NULL) {
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	if ( setjmp(png_jmpbuf(png_ptr)) ) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
	}

	png_init_io( png_ptr, fp );
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_png(
		png_ptr, info_ptr,
		PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL
	);

	info->width = png_get_image_width( png_ptr, info_ptr );
	info->height = png_get_image_height( png_ptr, info_ptr );
	info->alpha =
		( png_get_color_type( png_ptr, info_ptr ) == PNG_COLOR_TYPE_RGBA )
		?  true
		: false;

	u32 row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	info->data = new u8[ row_bytes * info->height ];

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for ( u32 i = 0; i < info->height; ++i ) {
		memcpy(
			info->data + ( row_bytes * (info->height-1-i) ),
			row_pointers[i],
			row_bytes
		);
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	return true;
}

namespace Baukasten {
	class ImagePrivate {
	public:
		ImagePrivate( const string path ) :
			mPath( path ), mInfo( new ImageInfo() )
		{
			mHandle = fopen( path.c_str(), "rb" );
			if ( !mHandle )
				BK_DEBUG( path << " couldn't be opened!" );

			mType = ::type( mHandle );
			mIsOpen = true;
		}

		virtual ~ImagePrivate()
		{
			fclose( mHandle );
			mHandle = 0;
			delete mInfo->data;
		}

		void
		close()
		{
			if ( isOpen() ) {
				fclose( mHandle );
				mIsOpen = false;
				mHandle = 0;
				delete mInfo->data;
			}
		}

		char*
		data() const
		{
			return mInfo->data;
		}

		vec2<int>
		dim() const
		{
			return { mInfo->width, mInfo->height };
		}

		int
		height() const
		{
			return mInfo->height;
		}

		bool
		isOpen() const
		{
			return mIsOpen;
		}

		void
		read()
		{
			bool result = false;

			switch ( mType ) {
			case Image::PNG:
				result = readPng( mHandle, mInfo );
				break;
			case Image::JPEG:
			case Image::GIF:
			case Image::NO_TYPE:
				break;
			}
		}

		int32
		size() const
		{
			return mInfo->size;
		}

		Image::ImageType
		type() const
		{
			return mType;
		}

		int
		width() const
		{
			return mInfo->width;
		}

	private:
		FILE*				mHandle;
		Image::ImageType	mType;
		string				mPath;
		bool				mIsOpen;
		ImageInfo*			mInfo;
	};
} /* Baukasten */

Image::Image( const string &path ) :
	mImpl( new ImagePrivate( path ) )
{
}

Image::~Image()
{
}

void
Image::close()
{
	mImpl->close();
}

char*
Image::data() const
{
	return mImpl->data();
}

vec2<int>
Image::dim() const
{
	return mImpl->dim();
}

int
Image::height() const
{
	return mImpl->height();
}

bool
Image::isOpen() const
{
	return mImpl->isOpen();
}

void
Image::read()
{
	mImpl->read();
}

int32
Image::size() const
{
	return mImpl->size();
}

Image::ImageType
Image::type() const
{
	return mImpl->type();
}

int
Image::width() const
{
	return mImpl->width();
}

