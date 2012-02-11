#ifndef GLFW_GRAPHICS_H_CMJ6TAUE
#define GLFW_GRAPHICS_H_CMJ6TAUE

#include "model/Global"

#include "core/Math"
#include "graphics/IGraphics"

namespace Baukasten {

	class CoreServices;
	class Form;
	class GlfwGraphicsP;

	class BAUKASTEN_EXPORT GlfwGraphics : public IGraphics {
	public:
		GlfwGraphics();
		virtual ~GlfwGraphics();

		int init( CoreServices* );

		void createWindow( const vec2<int>&, const std::wstring& );

		void render( Form* );
		void shutdown();

		void loadResource( const string&, const string& );
		void freeResource( const string& );

		void drawCircle( const vec3<float>&, const uint, const Colour& );
		void drawImage( const string&, const vec2<float>&, const vec3<float>& );
		void drawLine( const vec3<float>&, const vec3<float>&, const Colour& );
		void drawPoint( const vec3<float>&, const uint, const Colour& );
		void drawRect( const vec2<float>&, const vec3<float>&, const Colour& );
		void drawText( const wchar_t*, const vec3<float>&, const Colour& );

		string serviceName() const { return "GLFW"; }
		float fps() const;

		void setWindowCaption( const std::wstring& );

	private:
		GlfwGraphicsP*	mImpl;
		friend class GlfwGraphicsP;
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_GRAPHICS_H_CMJ6TAUE */

