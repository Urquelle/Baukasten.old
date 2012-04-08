#ifndef IMAGE_H_9GZDLWPR
#define IMAGE_H_9GZDLWPR

#include "core/Math"
#include "graphics/Global"

namespace Baukasten {
	class ImagePrivate;

	/*!
	 * \ingroup service
	 * @{
	 *
	 * \addtogroup graphics
	 * @{
	 *
	 * \class Image
	 * \headerfile Image "graphics/Image"
	 * \brief Image class.
	 *
	 * provides basic methods to deal with image files. several formats
	 * are supported due to the usage of FreeImage library.
	 */
	class BAUKASTEN_EXPORT Image {
	public:

		/*!
		 * \brief constructor.
		 * \param path path to the image file.
		 */
		explicit Image( const string& );

		/*! destructor */
		virtual ~Image();

		/*! closes the file and frees the used memory. */
		void       close();

		/*! returns the image data. */
		u8*        data() const;

		/*! returns the width/height of the image. */
		vec2<u32>  dim() const;

		/*!
		 * returns whether or not the image
		 * contains an alpha channel.
		 */
		bool       hasAlpha() const;

		/*!
		 * \brief height of the image.
		 * \return u32 height of the picture.
		 */
		u32        height() const;

		/*! tells whether the file's data was already read in. */
		bool       isRead() const;

		/*! returns path to the image file. */
		string     path() const;

		/*! read image's data from file into memory. */
		void       read();

		/*! file size in kilobytes. */
		u32        size() const;

		/*! width of the image. */
		u32        width() const;

	private:
		BK_PIMPL_PTR(Image);
	};
	/** @} */
	/** @} */
} /* Baukasten */

#endif /* end of include guard: IMAGE_H_9GZDLWPR */

