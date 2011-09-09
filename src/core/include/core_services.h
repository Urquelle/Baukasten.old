#ifndef CORE_SERVICES_8D741217
#define CORE_SERVICES_8D741217

#include "global.h"

namespace Baukasten {
	class IGraphics;
	class IInput;

	class BAUKASTEN_EXPORT CoreServices {
	public:
		static CoreServices* instance();
		virtual ~CoreServices();

		void init();
		IGraphics* getVideoService() const;
		IInput* getInputService() const;

	private:
		CoreServices();

		static CoreServices* mInstance;

		IGraphics*	mGraphics;
		IInput*		mInput;
	};
} /* Baukasten */

#endif /* end of include guard: CORE_SERVICES_8D741217 */
