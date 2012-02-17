#ifndef IMAGE_FUNCTIONS_H_JA5FSB6J
#define IMAGE_FUNCTIONS_H_JA5FSB6J

#include "model/Global"

#include <png.h>
#include <cstdlib>

using namespace Baukasten;

struct ImageInfo {
	u32 size, width, height, numberOfPasses, bitDepth;
	bool alpha;
	u8* data;
};

Image::ImageType
_type( FILE *f )
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

bool
_readPng( FILE *fp, ImageInfo *info )
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

bool
_readJpeg( FILE *fp, ImageInfo *info )
{
	BK_DEBUG( "implement me!" );
	return false;
}

bool
_readGif( FILE *fp, ImageInfo *info )
{
	BK_DEBUG( "implement me!" );
	return false;
}

#endif /* end of include guard: IMAGE_FUNCTIONS_H_JA5FSB6J */

