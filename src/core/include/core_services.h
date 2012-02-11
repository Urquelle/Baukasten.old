#ifndef CORE_SERVICES_8D741217
#define CORE_SERVICES_8D741217

#include "global.h"

namespace Baukasten {
	class IAudio;
	class IGraphics;
	class IInput;

	class BAUKASTEN_EXPORT CoreServices {
	public:
		static CoreServices* instance();
		virtual ~CoreServices();

		void init( int, char** );
		void shutdown();

		IAudio*		audioService() const;
		IInput*		inputService() const;
		IGraphics*	videoService() const;

		int			argumentsCount();
		char**		arguments() const;

	private:
		CoreServices();

		IAudio*		mAudio;
		IGraphics*	mGraphics;
		IInput*		mInput;

		int			mArgc;
		char**		mArgv;
	};
} /* Baukasten */

#endif /* end of include guard: CORE_SERVICES_8D741217 */
