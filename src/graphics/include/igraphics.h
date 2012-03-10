#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "core/Color"
#include "core/Math"
#include "graphics/Global"
#include "graphics/GraphicsInterface"

namespace Baukasten {
	class CoreServices;
	class Form;
	class Image;

	class BAUKASTEN_EXPORT IGraphics {
	public:
		IGraphics() : m_initialised( false ) {}

		bool isInitialised() const { return m_initialised; }

		virtual void createWindow( const vec2<u32>&, const wstring& ) = 0;
		virtual void drawCircle( const vec3<float>&, const u32, const Color& ) = 0;
		virtual void drawImage( const string&, const vec2<float>&,
				const vec3<float>& ) = 0;
		virtual void drawImage( Image&, const vec2<float>&,
				const vec3<float>& ) = 0;
		virtual void drawLine( const vec3<float>&, const vec3<float>&,
				const Color&, const float ) = 0;
		virtual void drawPoint( const vec3<float>&, const u32, const Color& ) = 0;
		virtual void drawRect( const vec2<float>&, const vec3<float>&,
				const Color& ) = 0;
		virtual void drawText( const string&, const vec3<float>&, const Color& ) = 0;
		virtual float fps() const = 0;
		virtual int init( CoreServices* ) = 0;
		virtual void render( Form* ) = 0;
		virtual string serviceName() const = 0;
		virtual void setWindowCaption( const wstring& ) = 0;
		virtual void setWindowSize( const u32, const u32 ) = 0;
		virtual void shutdown() = 0;

	protected:
		bool m_initialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
