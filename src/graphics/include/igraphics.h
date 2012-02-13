#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "model/Global"

#include "core/Color"
#include "core/Math"
#include "graphics/GraphicsInterface"

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

		virtual void drawCircle( const vec3<float>&, const int32, const Color& ) = 0;
		virtual void drawImage( const string&, const vec2<float>&, const vec3<float>& ) = 0;
		virtual void drawLine( const vec3<float>&, const vec3<float>&, const Color& ) = 0;
		virtual void drawPoint( const vec3<float>&, const int32, const Color& ) = 0;
		virtual void drawRect( const vec2<float>&, const vec3<float>&, const Color& ) = 0;
		virtual void drawText( const wchar_t*, const vec3<float>&, const Color& ) = 0;

		virtual string serviceName() const = 0;
		virtual float fps() const = 0;
		bool isInitialised() const { return mInitialised; }
		virtual void setWindowCaption( const std::wstring& ) = 0;

		// TODO: keep 3d in mind (frustum, z-coord, cams, ...)

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
