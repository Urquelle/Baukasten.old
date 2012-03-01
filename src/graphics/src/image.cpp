#include "graphics/Image"

#include "core/Debug"

#include "graphics/include/image_helper.h"

using namespace Baukasten;

namespace Baukasten {
	class ImagePrivate {
	public:
		ImagePrivate( const string path ) :
			m_info( new ImageInfo() ),
			m_path( path )
		{
			m_info->data = 0;
		}

		virtual ~ImagePrivate()
		{
			_free( m_info );
		}

		void
		close()
		{
			_free( m_info );
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
			_read( m_path, m_info );
		}

		u32
		size() const
		{
			return m_info->size;
		}

		u32
		width() const
		{
			return m_info->width;
		}

	private:
		ImageInfo*  m_info;
		string      m_path;
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

u32
Image::width() const
{
	return m_impl->width();
}

