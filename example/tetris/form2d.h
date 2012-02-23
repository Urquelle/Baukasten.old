#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include "model/Global"
#include "model/Form"

class Form2d : public Baukasten::Form {
public:
	Form2d( const std::string&, const std::string&, Baukasten::IGraphics* );
	virtual ~Form2d();

	void render();

private:
	string m_fileName;
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
