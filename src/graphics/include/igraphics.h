#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "global.h"
#include "../../util/Util"

#include "graphics_interface.h"
#include "colour.h"

namespace Baukasten {
	class Form;
	class CoreServices;

	class BAUKASTEN_EXPORT IGraphics {
	public:
		IGraphics() : mInitialised( false ) {}
		virtual int init( CoreServices* ) = 0;
		virtual void shutdown() = 0;

		virtual void render( Form* ) = 0;

		virtual void createWindow( const vec2<int>&, const std::wstring& ) = 0;

		virtual void drawCircle( const vec3<float>&, const uint, const Colour& ) = 0;
		virtual void drawImage( const string&, const vec2<float>&, const vec3<float>& ) = 0;
		virtual void drawLine( const vec3<float>&, const vec3<float>&, const Colour& ) = 0;
		virtual void drawPoint( const vec3<float>&, const uint, const Colour& ) = 0;
		virtual void drawRect( const vec2<float>&, const vec3<float>&, const Colour& ) = 0;
		virtual void drawText( const wchar_t*, const vec3<float>&, const Colour& ) = 0;

		virtual string getServiceName() const = 0;
		virtual float getFps() const = 0;
		bool isInitialised() const { return mInitialised; }
		virtual void setWindowCaption( const std::wstring& ) = 0;

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
