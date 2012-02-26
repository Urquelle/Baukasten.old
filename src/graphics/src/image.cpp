#include "graphics/Image"

#include "core/Debug"

#include "graphics/include/image_helper.h"

using namespace Baukasten;

namespace Baukasten {
	class ImagePrivate {
	public:
		ImagePrivate( const string path ) :
			m_path( path ), m_info( new ImageInfo() )
		{
			m_info->data = 0;
			m_handle = fopen( path.c_str(), "rb" );
			if ( !m_handle )
				BK_DEBUG( path << " couldn't be opened!" );

			m_type = _type( m_handle );
			m_isOpen = true;
		}

		virtual ~ImagePrivate()
		{
			if ( m_handle )
				fclose( m_handle );
			m_handle = 0;

			if ( m_info->data )
				delete m_info->data;
			m_info->data = 0;
		}

		void
		close()
		{
			if ( isOpen() ) {
				fclose( m_handle );
				m_isOpen = false;
				m_handle = 0;
				delete m_info->data;
				m_info->data = 0;
			}
		}

		u8*
		data() const
		{
			return m_info->data;
		}

		vec2<u32>
		dim() const
		{
			return { m_info->width, m_info->height };
		}

		bool
		hasAlpha() const
		{
			return m_info->alpha;
		}

		u32
		height() const
		{
			return m_info->height;
		}

		bool
		isOpen() const
		{
			return m_isOpen;
		}

		bool
		isRead() const
		{
			return m_info->data != 0;
		}

		string
		path() const
		{
			return m_path;
		}

		void
		read()
		{
			if ( isRead() ) return;

			bool result = false;

			switch ( m_type ) {
			case Image::PNG:
				result = _readPng( m_handle, m_info );
				break;
			case Image::JPEG:
				result = _readJpeg( m_handle, m_info );
				break;
			case Image::GIF:
				result = _readGif( m_handle, m_info );
				break;
			case Image::NO_TYPE:
				break;
			}
		}

		u32
		size() const
		{
			return m_info->size;
		}

		Image::ImageType
		type() const
		{
			return m_type;
		}

		u32
		width() const
		{
			return m_info->width;
		}

	private:
		FILE*				m_handle;
		Image::ImageType	m_type;
		string				m_path;
		bool				m_isOpen;
		ImageInfo*			m_info;
	};
} /* Baukasten */

Image::Image( const string &path ) :
	m_impl( new ImagePrivate( path ) )
{
}

Image::~Image()
{
	delete m_impl;
}

void
Image::close()
{
	m_impl->close();
}

u8*
Image::data() const
{
	return m_impl->data();
}

vec2<u32>
Image::dim() const
{
	return m_impl->dim();
}

bool
Image::hasAlpha() const
{
	return m_impl->hasAlpha();
}

u32
Image::height() const
{
	return m_impl->height();
}

bool
Image::isOpen() const
{
	return m_impl->isOpen();
}

bool
Image::isRead() const
{
	return m_impl->isRead();
}

string
Image::path() const
{
	return m_impl->path();
}

void
Image::read()
{
	m_impl->read();
}

u32
Image::size() const
{
	return m_impl->size();
}

Image::ImageType
Image::type() const
{
	return m_impl->type();
}

u32
Image::width() const
{
	return m_impl->width();
}

