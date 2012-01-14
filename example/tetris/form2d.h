#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include <global.h>

#include <form.h>

class Form2d : public Baukasten::Form {
public:
	Form2d( const std::string&, const std::string&, Baukasten::IGraphics* );
	virtual ~Form2d();

	void render();

private:
	string mFileName;
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
