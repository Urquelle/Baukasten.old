#include "core/Font"

#include "core/Color"
#include "core/Debug"

#include <cmath>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace Baukasten;

namespace Baukasten {
	class FontPrivate {
	public:
		FontPrivate( Font *f ) :
			m_master( f )
		{
			FT_Init_FreeType( &m_lib );
			FT_New_Face(
				m_lib, "/usr/share/fonts/corefonts/arial.ttf",
				0, &m_face
			);
			FT_Set_Char_Size( m_face, 12 * 64, 0, 100, 0 );
		}

		virtual ~FontPrivate()
		{
		}

		void setFace( const char *filePath )
		{
		}

		void setSize( const u32 size )
		{
			FT_Set_Char_Size( m_face, size * 64, 0, 100, 0 );
		}

		void render( const vec3<float> &pos, const char *text, const Color &c )
		{
			BK_ASSERT( m_face != 0, "couldn't load font!" );

			u32 numChars = strlen( text );
			FT_GlyphSlot slot = m_face->glyph;
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
				FT_Set_Transform( m_face, &matrix, &pen );
				FT_Load_Char( m_face, text[n], FT_LOAD_RENDER );
				pen.x += slot->advance.x;
				pen.y += slot->advance.y;
			}
		}

	private:
		Font* 		m_master;
		FT_Library	m_lib;
		FT_Face		m_face;
	};
} /* Baukasten */

Font::Font() :
	m_impl( new FontPrivate( this ) )
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
	m_impl->setFace( filePath );
}

void
Font::setSize( const u32 size )
{
	m_impl->setSize( size );
}

void
Font::render( const vec3<float> &pos, const char *text, const Color &c )
{
	m_impl->render( pos, text, c );
}

