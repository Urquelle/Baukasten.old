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

		IAudio*		getAudioService() const;
		IInput*		getInputService() const;
		IGraphics*	getVideoService() const;

		int			getArgumentsCount();
		char**		getArguments() const;

	private:
		CoreServices();

		static CoreServices* mInstance;

		IAudio*		mAudio;
		IGraphics*	mGraphics;
		IInput*		mInput;

		int			mArgc;
		char**		mArgv;
	};
} /* Baukasten */

#endif /* end of include guard: CORE_SERVICES_8D741217 */
