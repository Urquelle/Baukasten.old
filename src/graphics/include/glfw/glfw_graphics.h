#ifndef GLFW_GRAPHICS_H_CMJ6TAUE
#define GLFW_GRAPHICS_H_CMJ6TAUE

#include "core/Math"
#include "graphics/Global"
#include "graphics/IGraphics"

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

		void createWindow( const vec2<u32>&, const string& );
		void drawInfo( IFont*, const vec3<f32>&,
				bool compact, InfoFlags = DRAW_ALL );
		void drawCircle( const vec3<f32>&, const u32, const Color& );
		void drawImage( const string&, const vec2<f32>&, const vec3<f32>& );
		void drawImage( Image&, const vec2<f32>&, const vec3<f32>& );
		void drawLine( const vec3<f32>&, const vec3<f32>&,
				const Color&, const f32 );
		void drawPoint( const vec3<f32>&, const u32, const Color& );
		void drawPolygon( const vector<vec3<f32>>&,
				const Color&, bool outline = false );
		void drawRect( const vec2<f32>&, const vec3<f32>&,
				const Color&, bool outline = false );
		void drawText( IFont*, const string&, const vec3<f32>&, const Color& );
		f32 fps() const;
		void init( Services& );
		void render( Form* );
		void setWindowTitle( const string& );
		void setWindowSize( const u32, const u32 );
		void shutdown();
		f32 time() const;

	private:
		BK_PIMPL_PTR( GlfwGraphics );
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_GRAPHICS_H_CMJ6TAUE */

