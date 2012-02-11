#ifndef BLOCK_FORM_21IENA7S
#define BLOCK_FORM_21IENA7S

#include "model/Form"

class BlockForm : public Baukasten::Form {
public:
	const int BLOCK_WIDTH;
	const int BLOCK_HEIGHT;

	BlockForm( const string&, Baukasten::IGraphics* );
	virtual ~BlockForm();

	void render();
};

#endif /* end of include guard: BLOCK_FORM_21IENA7S */
