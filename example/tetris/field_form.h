#ifndef FIELD_FORM_D01BMD3U
#define FIELD_FORM_D01BMD3U

#include "core/Global"
#include "core/Form"

class FieldForm : public Baukasten::Form {
public:
	FieldForm( const string&, Baukasten::IGraphics* );
	virtual ~FieldForm();

	void render();
};

#endif /* end of include guard: FIELD_FORM_D01BMD3U */
