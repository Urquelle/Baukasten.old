#ifndef INPUTINTERFACE_AKBKP72C
#define INPUTINTERFACE_AKBKP72C

#include "input/Global"

class KeyEvent;

namespace Baukasten {
	class IInput;

	class BAUKASTEN_EXPORT InputInterface {
	public:
		static IInput* instance();

		virtual ~InputInterface();

	private:
		InputInterface();

		static IInput* m_instance;
	};
} /* Baukasten */

#endif /* end of include guard: INPUTINTERFACE_AKBKP72C */
