#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "global.h"

#include "graphics_interface.h"

namespace Baukasten {
	class Form;
	class CoreServices;

	class BAUKASTEN_EXPORT IGraphics {
	public:
		IGraphics() : mInitialised( false ) {}
		virtual int init( CoreServices* ) = 0;
		virtual void render( Form* ) = 0;
		virtual void shutDown() = 0;

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
