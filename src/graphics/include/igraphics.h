#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "global.h"

namespace Baukasten {
	class Form;

	class BAUKASTEN_EXPORT IGraphics {
	public:
		IGraphics() : mInitialised( false ) {}
		virtual int init() = 0;
		virtual void render() = 0;
		virtual void addForm( Form* ) = 0;
		virtual void shutDown() = 0;

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
