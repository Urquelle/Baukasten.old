#ifndef IAUDIO_H_YOASQ2PU
#define IAUDIO_H_YOASQ2PU

#include "global.h"

#include "audio_interface.h"

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT IAudio {
	public:
		IAudio() : mInitialised( false ) {}
		virtual int init( CoreServices* ) = 0;
		virtual void shutdown() = 0;

		virtual void loadFile( const std::string&, const std::string& ) = 0;
		virtual void freeResource( const std::string& ) = 0;

		virtual void play( const std::string& ) = 0;
		virtual void play( const std::string&, bool ) = 0;
		virtual void play( const std::string&, int, int, bool ) = 0;

		virtual void pause( const std::string& ) = 0;
		virtual void stop( const std::string& ) = 0;

	protected:
		bool mInitialised;
	};
} /* Baukasten */

#endif /* end of include guard: IAUDIO_H_YOASQ2PU */

