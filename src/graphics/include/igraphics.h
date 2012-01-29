#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "global.h"

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

		virtual void drawImage( const string&, const v2<float>&, const v3<float>& ) = 0;
		virtual void drawLine( const v3<float>&, const v3<float>&, const Colour& ) = 0;
		virtual void drawRect( const v2<float>&, const v3<float>&, const Colour& ) = 0;
		virtual void drawText( const wchar_t*, const v3<float>&, const Colour& ) = 0;
		virtual string getServiceName() const = 0;
		bool isInitialised() const { return mInitialised; }
		virtual void setWindowCaption( const std::wstring& ) = 0;

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
