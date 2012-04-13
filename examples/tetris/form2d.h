#ifndef WORLDMAP_FORM_OPYB550X
#define WORLDMAP_FORM_OPYB550X

#include "graphics/IGraphics"
#include "model/Form"
#include "model/Global"

using namespace Baukasten;

class Form2d : public Form {
public:
	Form2d( const string &id, const string &path ) :
        Form( id ),
        m_path( path )
    {
    }

	virtual ~Form2d()
    {
    }

	void render()
    {
        graphics().drawImage( m_path, size(), position() );
    }

private:
    string m_path;
};

#endif /* end of include guard: WORLDMAP_FORM_OPYB550X */
