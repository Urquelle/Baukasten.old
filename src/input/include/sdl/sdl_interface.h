#ifndef SDL_INTERFACE_JVOVMLE7
#define SDL_INTERFACE_JVOVMLE7

#include "global.h"

#include "iinput.h"

class SDL_Surface;

namespace Baukasten {
	class BAUKASTEN_EXPORT SDLInterface : public IInput {
	public:
		SDLInterface();
		virtual ~SDLInterface();

		bool init();
		void process() const;
		void shutDown();

		SDL_Surface* getScreen() const;

	private:
		SDL_Surface* mSurface;
	};
} /* Baukasten */

#endif /* end of include guard: SDL_INTERFACE_JVOVMLE7 */
