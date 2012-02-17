#include "core/Font"

#include "core/Color"
#include "model/Debug"

#include <cmath>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace Baukasten;

namespace Baukasten {
	class FontPrivate {
	public:
		FontPrivate( Font *f ) :
			mMaster( f )
		{
			FT_Init_FreeType( &mLib );
			FT_New_Face(
				mLib, "/usr/share/fonts/corefonts/arial.ttf",
				0, &mFace
			);
			FT_Set_Char_Size( mFace, 12 * 64, 0, 100, 0 );
		}

		virtual ~FontPrivate()
		{
		}

		void setFace( const char *filePath )
		{
		}

		void setSize( const u32 size )
		{
			FT_Set_Char_Size( mFace, size * 64, 0, 100, 0 );
		}

		void render( const vec3<float> &pos, const char *text, const Color &c )
		{
			BK_ASSERT( mFace != 0, "couldn't load font!" );

			u32 numChars = strlen( text );
			FT_GlyphSlot slot = mFace->glyph;
			FT_Vector pen;
			FT_Matrix matrix;

			auto angle = 0;

			matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
			matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
			matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
			matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

			pen.x = pos[BK_X];
			pen.y = pos[BK_Y];

			for (u32 n = 0; n < numChars; ++n) {
				FT_Set_Transform( mFace, &matrix, &pen );
				FT_Load_Char( mFace, text[n], FT_LOAD_RENDER );
				pen.x += slot->advance.x;
				pen.y += slot->advance.y;
			}
		}

	private:
		Font* 		mMaster;
		FT_Library	mLib;
		FT_Face		mFace;
	};
} /* Baukasten */

Font::Font() :
	mImpl( new FontPrivate( this ) )
{
}

Font::Font( const char *face )
{
	BK_DEBUG( "implement me" );
}

Font::~Font()
{
}

void
Font::setFace( const char *filePath )
{
	mImpl->setFace( filePath );
}

void
Font::setSize( const u32 size )
{
	mImpl->setSize( size );
}

void
Font::render( const vec3<float> &pos, const char *text, const Color &c )
{
	mImpl->render( pos, text, c );
}
