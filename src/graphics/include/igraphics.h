#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

namespace Baukasten {
	class Form;

	class IGraphics {
	public:
		IGraphics() : mInitialised( false ) {}
		virtual int init() = 0;
		virtual void render() = 0;
		virtual void addForm( Form* ) = 0;

	protected:
		bool mInitialised;
	};
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
