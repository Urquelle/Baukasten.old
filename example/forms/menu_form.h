#ifndef MENU_NR2276VJ
#define MENU_NR2276VJ

#include <irrlicht/irrlicht_form.h>

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

namespace irr {
	namespace gui {
		class IGUIListBox;
	} /* gui */
} /* irr */

class MenuForm : public Baukasten::IrrlichtForm {
public:
	MenuForm( const std::string&, Baukasten::IGraphics* );
	virtual ~MenuForm();

	void render();

	void setVisible( bool );

private:
	irr::gui::IGUIListBox* mMenu;
	/* data */
};

#endif /* end of include guard: MENU_NR2276VJ */

