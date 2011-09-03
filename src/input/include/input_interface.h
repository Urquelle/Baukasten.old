#ifndef INPUTINTERFACE_AKBKP72C
#define INPUTINTERFACE_AKBKP72C

#include "global.h"

#include <sigc++/sigc++.h>
#include <SDL/SDL.h>

namespace Baukasten {
	typedef sigc::signal<void, SDL_Event*> InputEvent;
	typedef sigc::signal<void, SDLKey, SDLMod> KeyDownEvent;

	class BAUKASTEN_EXPORT InputInterface {
	public:
		InputInterface();
		virtual ~InputInterface();

		bool init();
		void process() const;
		void shutDown();

		InputEvent onEvent() const;
		KeyDownEvent onKeyDown() const;

	private:
		SDL_Event*		mEvent;
		InputEvent		mOnEvent;
		KeyDownEvent	mOnKeyDown;
	};
} /* Baukasten */

#endif /* end of include guard: INPUTINTERFACE_AKBKP72C */
