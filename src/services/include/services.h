#pragma once

#include "services/Global"

namespace Baukasten {
	class IAudio;
	class IGraphics;
	class IInput;

	class BAUKASTEN_EXPORT Services {
	public:
		static Services* instance();
		virtual ~Services();

		void init( int, char** );
		void shutdown();

		IAudio*     audioService() const;
		IInput*     inputService() const;
		IGraphics*  videoService() const;

		int         argc();
		char**      argv() const;

	private:
		Services();

		IAudio*     m_audio;
		IGraphics*  m_graphics;
		IInput*     m_input;
		int         m_argc;
		char**      m_argv;
	};
} /* Baukasten */

