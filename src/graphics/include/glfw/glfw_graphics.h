#ifndef GLFW_GRAPHICS_H_CMJ6TAUE
#define GLFW_GRAPHICS_H_CMJ6TAUE

#include "global.h"

#include "igraphics.h"

namespace Baukasten {

	class CoreServices;
	class Form;
	class GlfwGraphicsP;

	class BAUKASTEN_EXPORT GlfwGraphics : public IGraphics {
	public:
		GlfwGraphics();
		virtual ~GlfwGraphics();

		int init( CoreServices* );

		void createWindow( const v2<int>&, const std::wstring& );

		void render( Form* );
		void shutdown();

		void loadResource( const string&, const string& );
		void freeResource( const string& );

		void drawCircle( const v3<float>&, const uint, const Colour& );
		void drawImage( const string&, const v2<float>&, const v3<float>& );
		void drawLine( const v3<float>&, const v3<float>&, const Colour& );
		void drawPoint( const v3<float>&, const uint, const Colour& );
		void drawRect( const v2<float>&, const v3<float>&, const Colour& );
		void drawText( const wchar_t*, const v3<float>&, const Colour& );

		string getServiceName() const { return "GLFW"; }

		void setWindowCaption( const std::wstring& );

	private:
		GlfwGraphicsP*	mImpl;
		friend class GlfwGraphicsP;
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_GRAPHICS_H_CMJ6TAUE */

