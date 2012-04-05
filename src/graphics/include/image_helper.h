#ifndef IMAGE_FUNCTIONS_H_JA5FSB6J
#define IMAGE_FUNCTIONS_H_JA5FSB6J

#include "graphics/Global"

#include <FreeImage.h>

using namespace Baukasten;

struct ImageInfo {
	u32 size, width, height, numberOfPasses, bitDepth;
	bool alpha;
	u8* data;
};

static void
_read( const string &path, ImageInfo *info )
{
	FreeImage_Initialise( true );

	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType( path.c_str(), 0 );
	FIBITMAP *image = FreeImage_Load( fif, path.c_str(), 0 );

	// convert image to be of format BGRA
	image = FreeImage_ConvertTo32Bits( image );

	info->width = FreeImage_GetWidth( image );
	info->height = FreeImage_GetHeight( image );
	info->size = info->width * info->height * 4;

	u8 *pixels = static_cast<u8*>( FreeImage_GetBits( image ) );
	info->data = new u8[ info->size ];

	// convert BGRA to RGBA
	for( int i = 0; i < info->width * info->height; i++ ) {
		info->data[i*4+0]= pixels[i*4+2];
		info->data[i*4+1]= pixels[i*4+1];
		info->data[i*4+2]= pixels[i*4+0];
		info->data[i*4+3]= pixels[i*4+3];
	}
}

static void
_free( ImageInfo *info )
{
	if ( info->data ) {
		delete info->data;
		info->data = 0;
	}
}

#endif /* end of include guard: IMAGE_FUNCTIONS_H_JA5FSB6J */

