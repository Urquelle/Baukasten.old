#ifndef GLFW_GRAPHICS_H_CMJ6TAUE
#define GLFW_GRAPHICS_H_CMJ6TAUE

#include "core/Math"
#include "graphics/Global"
#include "graphics/IGraphics"

namespace Baukasten {

	class CoreServices;
	class Form;
	class GlfwGraphicsPrivate;
	class IFont;
	class Image;

	class BAUKASTEN_EXPORT GlfwGraphics : public IGraphics {
	public:
		GlfwGraphics();
		virtual ~GlfwGraphics();

		void createWindow( const vec2<u32>&, const wstring& );
		void drawCircle( const vec3<float>&, const u32, const Color& );
		void drawImage( const string&, const vec2<float>&, const vec3<float>& );
		void drawImage( Image&, const vec2<float>&, const vec3<float>& );
		void drawLine( const vec3<float>&, const vec3<float>&,
				const Color&, const float );
		void drawPoint( const vec3<float>&, const u32, const Color& );
		void drawRect( const vec2<float>&, const vec3<float>&, const Color& );
		void drawText( const string&, const vec3<float>&, const Color& );
		void drawText( IFont*, const string&, const vec3<float>&, const Color& );
		float fps() const;
		int init( CoreServices* );
		void render( Form* );
		string serviceName() const { return "GLFW"; }
		void setWindowCaption( const wstring& );
		void setWindowSize( const u32, const u32 );
		void shutdown();

	private:
		BK_PIMPL_PTR( GlfwGraphics );
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_GRAPHICS_H_CMJ6TAUE */

