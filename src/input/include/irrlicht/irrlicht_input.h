#ifndef IRRLICHT_INPUT_CUT4Y0VU
#define IRRLICHT_INPUT_CUT4Y0VU

#include "global.h"

#include "iinput.h"

#include <irrlicht/IEventReceiver.h>

namespace irr {
	class IrrlichtDevice;
} /* irr */

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT IrrlichtInput :
		public IInput, public irr::IEventReceiver {
	public:
		IrrlichtInput();
		virtual ~IrrlichtInput();

		bool init( CoreServices* );
		void process() const;
		void shutDown();

		bool OnEvent( const irr::SEvent& );

		void setDevice( irr::IrrlichtDevice* );

	private:
		irr::IrrlichtDevice* mDevice;
	};
} /* Baukasten */

#endif /* end of include guard: IRRLICHT_INPUT_CUT4Y0VU */
