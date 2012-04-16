#ifndef GLFW_GRAPHICS_H_CMJ6TAUE
#define GLFW_GRAPHICS_H_CMJ6TAUE

#include "graphics/Global"
#include "graphics/IGraphics"
#include "math/Vector"
#include "math/Vector2"
#include "math/Vector3"

namespace Baukasten {

	class Form;
	class GlfwGraphicsPrivate;
	class IFont;
	class Image;
	class Services;

	class BAUKASTEN_EXPORT GlfwGraphics : public IGraphics {
	public:
		GlfwGraphics();
		virtual ~GlfwGraphics();

		void createWindow( const Vector<u32, 2>&, const string&, WindowFlags );
		void drawInfo( IFont*, const Vector3&,
				bool compact, InfoFlags = DRAW_ALL );
		void drawCircle( const Vector3&, const u32, const Color& );
		void drawImage( const string&, const Vector2&, const Vector3& );
		void drawImage( Image&, const Vector2&, const Vector3& );
		void drawLine( const Vector3&, const Vector3&,
				const Color&, const f32 );
		void drawPoint( const Vector3&, const u32, const Color& );
		void drawPolygon( const vector<Vector3>&,
				const Color&, bool outline = false );
		void drawRect( const Vector2&, const Vector3&,
				const Color&, bool outline = false );
		void drawText( IFont*, const string&, const Vector3&, const Color& );
		f32 fps() const;
		void init( Services& );
		void render( Form* );
		void setWindowTitle( const string& );
		void setWindowSize( const u32, const u32 );
		void shutdown();
		f32 time() const;

	private:
		BK_IMPL_PTR( GlfwGraphics );
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_GRAPHICS_H_CMJ6TAUE */

