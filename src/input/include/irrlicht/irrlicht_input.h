#ifndef IRRLICHT_INPUT_CUT4Y0VU
#define IRRLICHT_INPUT_CUT4Y0VU

#include "global.h"

#include "iinput.h"

namespace irr {
	class IrrlichtDevice;
} /* irr */

namespace Baukasten {
	class CoreServices;
	class IrrlichtInputPrivate;

	class BAUKASTEN_EXPORT IrrlichtInput :
		public IInput {
	public:
		IrrlichtInput();
		virtual ~IrrlichtInput();

		bool init( CoreServices* );
		void process() const;
		void shutdown();
		string serviceName() const { return "Irrlicht"; }

		void setDevice( irr::IrrlichtDevice* );

	private:
		shared_ptr<IrrlichtInputPrivate> mImpl;
		friend class IrrlichtInputPrivate;
		irr::IrrlichtDevice* mDevice;
	};
} /* Baukasten */

#endif /* end of include guard: IRRLICHT_INPUT_CUT4Y0VU */
