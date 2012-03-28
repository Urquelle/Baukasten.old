#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "core/Color"
#include "core/Math"
#include "graphics/Global"
#include "graphics/GraphicsInterface"
#include "services/IService"

namespace Baukasten {
	class Form;
	class IFont;
	class Image;
	class Services;

	/*!
	 * \brief Graphics interface declaration.
	 *
	 * \ingroup graphics interface
	 */
	class BAUKASTEN_EXPORT IGraphics : public IService {
	public:
		enum InfoFlags {
			DRAW_FPS     = 1 << 0,
			DRAW_VERSION = 1 << 1,
			DRAW_TIME    = 1 << 2,
			DRAW_ALL     = DRAW_FPS + DRAW_VERSION + DRAW_TIME
		};

		IGraphics( const string &name ) : IService( name ) {}

		virtual void createWindow( const vec2<u32>&, const wstring& ) = 0;
		virtual void drawInfo( const vec3<float>&,
				bool compact = false, InfoFlags = DRAW_ALL ) = 0;
		virtual void drawCircle( const vec3<float>&, const u32, const Color& ) = 0;
		virtual void drawImage( const string&, const vec2<float>&,
				const vec3<float>& ) = 0;
		virtual void drawImage( Image&, const vec2<float>&,
				const vec3<float>& ) = 0;
		virtual void drawLine( const vec3<float>&, const vec3<float>&,
				const Color&, const float ) = 0;
		virtual void drawPoint( const vec3<float>&, const u32, const Color& ) = 0;
		virtual void drawPolygon( const vector<vec3<float> >&,
				const Color&, bool outline = false ) = 0;
		virtual void drawRect( const vec2<float>&, const vec3<float>&,
				const Color&, bool outline = false ) = 0;
		virtual void drawText( const string&, const vec3<float>&, const Color& ) = 0;
		virtual void drawText( IFont*, const string&,
				const vec3<float>&, const Color& ) = 0;
		virtual float fps() const = 0;
		virtual void render( Form* ) = 0;
		virtual void setWindowCaption( const wstring& ) = 0;
		virtual void setWindowSize( const u32, const u32 ) = 0;
		virtual void shutdown() = 0;
		virtual float time() const = 0;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
