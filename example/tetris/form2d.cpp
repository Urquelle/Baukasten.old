#include "form2d.h"

#include <igraphics.h>

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
	getGraphics()->drawImage( mFileName, getSize(), getPosition() );
	Form::render();
}

