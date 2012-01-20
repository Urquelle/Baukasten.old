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
		virtual void shutdown() {}

		virtual void render( Form* ) = 0;
		virtual void shutDown() = 0;

		virtual void drawImage( const string&, const t_size&, const t_pos& ) = 0;
		virtual void drawLine( const t_pos&, const t_pos&, const Colour& ) = 0;
		virtual void drawRect( const t_size&, const t_pos&, const Colour& ) = 0;
		virtual void drawText( const wchar_t*, const t_pos&, const Colour& ) = 0;

		virtual void setWindowCaption( const std::wstring& ) = 0;

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
