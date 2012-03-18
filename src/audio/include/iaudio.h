#ifndef IAUDIO_H_YOASQ2PU
#define IAUDIO_H_YOASQ2PU

#include "audio/AudioInterface"
#include "audio/Global"

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT IAudio {
	public:
		IAudio() : m_initialised( false ) {}
		virtual int init( CoreServices* ) = 0;
		virtual void shutdown() = 0;

		virtual void loadFile( const string&, const string& ) = 0;
		virtual void freeResource( const string& ) = 0;


		virtual void play( const string& ) = 0;
		virtual void play( const string&, bool ) = 0;
		virtual void play( const string&, u32, u32, bool ) = 0;

		virtual void pause( const string& ) = 0;
		virtual void stop( const string& ) = 0;

	protected:
		bool m_initialised;
	};
} /* Baukasten */

#endif /* end of include guard: IAUDIO_H_YOASQ2PU */

