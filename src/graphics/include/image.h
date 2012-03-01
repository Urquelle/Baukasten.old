#ifndef IMAGE_H_9GZDLWPR
#define IMAGE_H_9GZDLWPR

#include "core/Math"
#include "graphics/Global"

namespace Baukasten {
	class ImagePrivate;

	class BAUKASTEN_EXPORT Image {
	public:
		explicit Image( const string& );
		virtual ~Image();

		void       close();
		u8*        data() const;
		vec2<u32>  dim() const;
		bool       hasAlpha() const;
		u32        height() const;
		bool       isRead() const;
		string     path() const;
		void       read();
		u32        size() const;
		u32        width() const;

	private:
		BK_PIMPL_PTR(Image);
	};
} /* Baukasten */

#endif /* end of include guard: IMAGE_H_9GZDLWPR */

