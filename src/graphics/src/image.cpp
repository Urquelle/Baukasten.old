#include "graphics/Image"

#include "core/Debug"

#include "graphics/include/image_functions.h"

using namespace Baukasten;

namespace Baukasten {
	class ImagePrivate {
	public:
		ImagePrivate( const string path ) :
			mPath( path ), mInfo( new ImageInfo() )
		{
			mHandle = fopen( path.c_str(), "rb" );
			if ( !mHandle )
				BK_DEBUG( path << " couldn't be opened!" );

			mType = _type( mHandle );
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

		u8*
		data() const
		{
			return mInfo->data;
		}

		vec2<u32>
		dim() const
		{
			return { mInfo->width, mInfo->height };
		}

		bool
		hasAlpha() const
		{
			return mInfo->alpha;
		}

		u32
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
				result = _readPng( mHandle, mInfo );
				break;
			case Image::JPEG:
				result = _readJpeg( mHandle, mInfo );
				break;
			case Image::GIF:
				result = _readGif( mHandle, mInfo );
				break;
			case Image::NO_TYPE:
				break;
			}
		}

		u32
		size() const
		{
			return mInfo->size;
		}

		Image::ImageType
		type() const
		{
			return mType;
		}

		u32
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

u8*
Image::data() const
{
	return mImpl->data();
}

vec2<u32>
Image::dim() const
{
	return mImpl->dim();
}

bool
Image::hasAlpha() const
{
	return mImpl->hasAlpha();
}

u32
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

u32
Image::size() const
{
	return mImpl->size();
}

Image::ImageType
Image::type() const
{
	return mImpl->type();
}

u32
Image::width() const
{
	return mImpl->width();
}

