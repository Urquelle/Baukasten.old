#ifndef FIELD_FORM_D01BMD3U
#define FIELD_FORM_D01BMD3U

#include <global.h>

#include <form.h>

class FieldForm : public Baukasten::Form {
public:
	FieldForm( const string&, Baukasten::IGraphics* );
	virtual ~FieldForm();

	void render();
};

#endif /* end of include guard: FIELD_FORM_D01BMD3U */
