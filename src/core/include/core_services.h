#ifndef CORE_SERVICES_8D741217
#define CORE_SERVICES_8D741217

#include "model/Global"

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

		IAudio*     audioService() const;
		IInput*     inputService() const;
		IGraphics*  videoService() const;

		int         argc();
		char**      argv() const;

	private:
		CoreServices();

		IAudio*     m_audio;
		IGraphics*  m_graphics;
		IInput*     m_input;
		int         m_argc;
		char**      m_argv;
	};
} /* Baukasten */

#endif /* end of include guard: CORE_SERVICES_8D741217 */
