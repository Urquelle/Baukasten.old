#ifndef IRRLICHT_FORM_1HID54U9
#define IRRLICHT_FORM_1HID54U9

#include "global.h"

#include "form.h"

namespace Baukasten {
	class IrrlichtGraphics;

	class IrrlichtForm : public Form {
	public:
		IrrlichtForm( const std::string&, IrrlichtGraphics* );
		virtual ~IrrlichtForm();

		IrrlichtGraphics* getGraphics() const;

	private:
		IrrlichtGraphics* mGraphics;
	};
} /* Baukasten */

#endif /* end of include guard: IRRLICHT_FORM_1HID54U9 */
