#include "form2d.h"

#include "graphics/IGraphics"

using namespace Baukasten;

Form2d::Form2d( const std::string &id, const std::string &fileName, IGraphics *graphics ) :
	Form( id, graphics ),
	mFileName( fileName )
{
}

Form2d::~Form2d()
{
}

void Form2d::render()
{
	graphics()->drawImage( mFileName, size(), position() );
}

