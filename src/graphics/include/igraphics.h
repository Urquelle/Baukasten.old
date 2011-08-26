#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

namespace Baukasten {
	class Form;

	class IGraphics {
	public:
		virtual void init() = 0;
		virtual void renderForm( Form* ) = 0;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
