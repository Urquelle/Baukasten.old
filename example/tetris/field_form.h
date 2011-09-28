#ifndef FIELD_FORM_D01BMD3U
#define FIELD_FORM_D01BMD3U

#include <irrlicht/irrlicht_form.h>

namespace Baukasten {
	class IGraphics;
} /* Baukasten */

class FieldForm : public Baukasten::IrrlichtForm {
public:
	FieldForm( const string&, Baukasten::IGraphics* );
	virtual ~FieldForm();

	void render();
};

#endif /* end of include guard: FIELD_FORM_D01BMD3U */
