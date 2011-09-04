#ifndef CORE_SERVICES_8D741217
#define CORE_SERVICES_8D741217

#include "global.h"

namespace Baukasten {
	typedef enum Services { INPUT, VIDEO, ALL } Services;

	class IGraphics;
	class IInput;

	class BAUKASTEN_EXPORT CoreServices {
	public:
		CoreServices();
		virtual ~CoreServices();

		void init( const Services& );
		IGraphics* getVideoService() const;
		IInput* getInputService() const;

	private:
		IGraphics*	mGraphics;
		IInput*		mInput;
	};
} /* Baukasten */

#endif /* end of include guard: CORE_SERVICES_8D741217 */
